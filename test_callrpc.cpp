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
#include "MySocket.h"
#include <iostream>
#include <fstream>
// #include "CustMapMain.h"

int main() {
    
    printf("Client Console\n\n");
    
    MySocket socket;
    socket.bind(64000);
    
    CustomString * customString = new CustomString("Ya rab");    
    
    std::vector<CustomObject *> parameters = {customString};
    
    MarshalledMessage marshalledMessage;
    
    marshal(marshalledMessage, parameters);
    
    Message sentMessage(marshalledMessage);
    
    sentMessage.setMessageType(Request);
    sentMessage.setRpcOperation(2);
    sentMessage.setRpcRequestID(1);
        
    std::cout<<"Sending RPC argument"<<std::endl;
    
    sentMessage.setDestIPAddress("127.0.0.1");
    sentMessage.setDestPortNumber(63000);
    

    Message returnValue = socket.callRPC(sentMessage);
        
 //   std::vector<CustomObject* > returnValues = {new CustomVector()};
    std::vector<CustomObject* > returnValues = {new CustomString()};
    
    unmarshal(returnValue, returnValues);

    // CustomVector * returnValueString = 
    //     dynamic_cast<CustomVector *>(returnValues[0]);
    
    // for(auto& item : returnValueString->getValue())
    // {
    //     puts(item.c_str());
    //     printf("item %s", item.c_str());
    // }
    
    CustomString* returnString = dynamic_cast<CustomString*> (returnValues[0]);
    //puts(returnString->getValue().c_str());

    std::ofstream file("myrecievedImage.png", std::ofstream::binary);
    
    if(file.is_open()){
        file.write(returnString->getValue().c_str(),
        returnString->getValue().size());
    
        file.close();
    }else{
        puts("failed to write image");
    }

    std::cout<<"Done"<<std::endl;

    return 0;
}

