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
#include "Message.h"
#include "UDPSocket.h"
#include "Packet.h"
#include "MySocket.h"
#include <iostream>

int main() {
    
    CustomString * customString = new CustomString("Argument Message: Nawawy");
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
    
    sentMessage.fillHeaders();
    
//    sentMessage.setMessageType(Acknowledgement);
//    sentMessage.setRpcOperation(1);
//    sentMessage.setRpcOperation(2);
    
    std::cout<<"Sedning RPC argument"<<std::endl;
    
    MySocket socket;
    socket.bind(64000);
    
    Packet packet("10.40.48.60", 64000);
    packet.setPacketMessage(sentMessage);
    
    Message returnValue = socket.callRPC(packet);
    
    returnValue.extractHeaders();
    
    std::vector<CustomObject* > returnValues = {new CustomString()};
    
    unmarshal(returnValue, returnValues);

    CustomString * returnValueString = dynamic_cast<CustomString *>(returnValues[0]);
    
    std::cout<<"Received RPC return value"<<std::endl;
    
    std::cout<<returnValueString->getValue()<<std::endl;
    
}
