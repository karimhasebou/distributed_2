//
//  main2.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/19/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Marshalling/MarshallingManager.h"
#include "CustomObjects/CustomInt.h"
#include "CustomObjects/CustomString.h"
#include "CustomObjects/CustomObject.h"
#include "Marshalling/MarshalledMessage.h"
#include "CustomObjects/CustomVector.h"
#include "CustomObjects/CustomBool.h"
#include "Message.h"
#include "UDPSocket.h"
#include "Packet.h"
#include "MySocket.h"
#include <iostream>

int main() {
    
    MySocket socket;
    socket.bind(64000);
    
    Packet recievedPacket;
    
    socket.recvFrom(recievedPacket);
    
    MarshalledMessage marshalledMessage = recievedPacket.getMessage();
    
    std::vector<CustomObject* > receivedValues = {new CustomString()};
    
    unmarshal(marshalledMessage, receivedValues);
    
    CustomString * returnValueString = dynamic_cast<CustomString *>(receivedValues[0]);
    
    std::cout<<"Received Argument"<<std::endl;
    
    std::cout<<returnValueString->getValue()<<std::endl;
    
    CustomString * replyString = new CustomString("Reply Message: Kareem");
    
    CustomObject * bigBoss = replyString;
    
    std::vector<CustomObject*> paramteres = {bigBoss};
    
    MarshalledMessage marshalled;
    
    marshal(marshalled, paramteres);
    
    Message replyMessage(marshalled);
    
    recievedPacket.setMessage(replyMessage);
    
    std::cout<<"Sending reply message"<<std::endl;

    socket.reply(recievedPacket);
    
}
