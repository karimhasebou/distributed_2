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
    
    printf("Server Console \n\n");
    
    MySocket socket;
    socket.bind(63000);
    
    Message receivedMessage;
    
    socket.recvFrom(receivedMessage);
        
    MarshalledMessage marshalledMessage = (MarshalledMessage)receivedMessage;
    
    std::vector<CustomObject* > receivedValues = {new CustomString()};
    
    unmarshal(marshalledMessage, receivedValues);
    
    CustomString * returnValueString = dynamic_cast<CustomString *>(receivedValues[0]);
    
    std::cout<<"Received Argument"<<std::endl;
    
    std::cout<<returnValueString->getValue()<<std::endl;
    
    std::string bigString = "";
    
    for (int i = 0; i < 1000; i++) {
        
        bigString += "Message" + std::to_string(i);
        
    }
    
    CustomString * replyString = new CustomString(bigString);
    
    CustomObject * bigBoss = replyString;
    
    std::vector<CustomObject*> paramteres = {bigBoss};
    
    MarshalledMessage marshalled;
    
    marshal(marshalled, paramteres);
    
    Message replyMessage(marshalled);
    
    replyMessage.setSocketAddress(receivedMessage.getSocketAddress());
    
    replyMessage.setMessageType(Reply);
    replyMessage.setRpcRequestID(1);
    replyMessage.setRpcOperation(1);
    
    std::cout<<"Sending reply message"<<std::endl;

    socket.reply(replyMessage);
    
    std::cout<<"Done"<<std::endl;
    
}
