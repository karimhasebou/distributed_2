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
#include "UDPLayer/UDPSocket.h"
#include "UDPLayer/MySocket.h"
#include <iostream>
#include <fstream>
// #include "CustMapMain.h"

int main() {
    
    printf("Client Console\n\n");
    
    MySocket socket;
    socket.bind(64000);
    
    std::string bigbig = "";
    for (int i = 0; i < 100000; i++) {
        bigbig = "HarryPotter" + std::to_string(i);
    }
    
    CustomString * customString = new CustomString(bigbig);
    
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
    
    socket.callRPC(sentMessage);
    
    std::cout<<"Done"<<std::endl;

    return 0;
}

