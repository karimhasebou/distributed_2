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
#include "UDPSocket.h"
#include "Packet.h"
#include "MySocket.h"
#include <iostream>
// #include "CustMapMain.h"
/*
int main() {
    
    printf("Client Console\n\n");
    
    MySocket socket;
    socket.bind(64000);
    
    CustomString * customString = new CustomString("Ya rab");
//    CustomInt * customInt = new CustomInt(14);
//    CustomVector * customVector = new CustomVector();
//    CustomBool * customBool = new CustomBool(false);
//    customVector->push_back("lol\nkkk");
//    customVector->push_back("144");
    
    CustomObject * bigboss = customString;
//    CustomObject * miniBoss = customInt;
//    CustomObject * microBoss = customVector;
//    CustomObject * nanoBoss = customBool;
    
    std::vector<CustomObject *> parameters = {bigboss};
//    , miniBoss, microBoss, nanoBoss};
    
    MarshalledMessage marshalledMessage;
    
    marshal(marshalledMessage, parameters);
    
    Message sentMessage(marshalledMessage);
    
    sentMessage.setMessageType(Request);
    sentMessage.setRpcOperation(1);
    sentMessage.setRpcRequestID(1);
        
//    sentMessage.setMessageType(Acknowledgement);
//    sentMessage.setRpcOperation(1);
//    sentMessage.setRpcOperation(2);
    
    std::cout<<"Sending RPC argument"<<std::endl;
    
    sentMessage.setDestIPAddress("127.0.0.1");
    sentMessage.setDestPortNumber(63000);
    

    Message returnValue = socket.callRPC(sentMessage);
        
    std::vector<CustomObject* > returnValues = {new CustomString()};
    
    unmarshal(returnValue, returnValues);

    CustomString * returnValueString = dynamic_cast<CustomString *>(returnValues[0]);
    
    std::cout<<"Received RPC return value"<<std::endl;
    
    std::cout<<returnValueString->getValue()<<std::endl;
    
    std::cout<<"Done"<<std::endl;
}
*/
