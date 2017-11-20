//
//  main.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/15/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Marshalling/MarshallingManager.h"
#include "CustomObjects/CustomInt.h"
#include "CustomObjects/CustomString.h"
#include "CustomObjects/CustomObject.h"
#include "Marshalling/MarshalledMessage.h"
#include "CustomObjects/CustomVector.h"
#include "CustomObjects/CustomBool.h"
#include "CustomObjects/CustomMap.h"
#include "Message.h"
#include "UDPSocket.h" #include "Datagram.h"
#include <iostream>
// #include "CustMapMain.h"
/*
int main() {
    
    CustomString * customString = new CustomString("rida is happy");
    CustomInt * customInt = new CustomInt(14);
    CustomVector * customVector = new CustomVector();
    CustomBool * customBool = new CustomBool(false);
    customVector->push_back("lol\nkkk");
    customVector->push_back("144");

    
    CustomObject * bigboss = customString;
    CustomObject * miniBoss = customInt;
    CustomObject * microBoss = customVector;
    CustomObject * nanoBoss = customBool;
   
    std::vector<CustomObject *> parameters = {bigboss, miniBoss, microBoss, nanoBoss};
    
    MarshalledMessage marshalledMessage;
    
    marshal(marshalledMessage, parameters);
    
    Message sentMessage(marshalledMessage);
    
    sentMessage.setMessageType(Acknowledgement);
    sentMessage.setRpcOperation(1);
    sentMessage.setRpcOperation(2);
    
    UDPSocket socket;
    socket.bind(64000);
    
    Datagram datagram("10.40.32.184", 64000);
    datagram.setMessage(sentMessage);
    
    socket.sendDatagram(datagram);
    
    std::cout<<"Sent Packet"<<std::endl;
    
}
*/
