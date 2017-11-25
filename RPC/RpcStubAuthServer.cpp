//
//  RpcStubAuthServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RpcStub.h"
#include "RpcCalls.h"
#include <vector>
#include "../Marshalling/MarshallingManager.h"
#include "../Marshalling/MarshalledMessage.h"
#include "../CustomObjects/CustomInt.h"
#include "../CustomObjects/CustomString.h"
#include "../CustomObjects/CustomObject.h"
#include "../CustomObjects/CustomVector.h"
#include "../CustomObjects/CustomBool.h"
#include "../UDPLayer/MySocket.h"

Message login(Message& messageParamters) {
    
    std::vector<CustomObject *> parameters = {new CustomString(), new CustomString()};
    
    unmarshal(messageParamters, parameters);
    
    std::string username = (dynamic_cast<CustomString *>(parameters[0]))->getValue();
    
    std::string password = (dynamic_cast<CustomString *>(parameters[1]))->getValue();

    LoginStatus status = authserver::login(username, password);

    CustomInt * loginStatus = new CustomInt((int)status);
    
    std::vector<CustomObject *> returnValues = {dynamic_cast<CustomObject*>(loginStatus)};
    
    Message replyMessage;
    
    replyMessage.setSocketAddress(messageParamters.getSocketAddress());
    
    marshal(replyMessage, returnValues);
    
    return replyMessage;
    
}

Message getIPAddress(Message& messageParamters) {
    
    CustomVector * ipAddresses = new CustomVector(authserver::getIPAddress());
    
    struct in_addr ipAddr = messageParamters.getSocketAddress().sin_addr;
    char myIPChar[15];
    inet_ntop(AF_INET, &ipAddr, myIPChar, 15);
    
    printf("My IP adrress is %s\n", myIPChar);
    
    std::vector<CustomObject*> returnValues = {dynamic_cast<CustomObject*>(ipAddresses)};
    
    Message replyMessage;
    
    replyMessage.setSocketAddress(messageParamters.getSocketAddress());
        
    marshal(replyMessage, returnValues);
    
    return replyMessage;
}

Message getUsername(Message& messageParamters)
{
    std::vector<CustomObject *> parameters = {new CustomString()};
    
    unmarshal(messageParamters, parameters);
    
    std::string IPAddress = (dynamic_cast<CustomString *>(parameters[0]))->getValue();

    std::string username_val = authserver::getUsername(IPAddress);
    
    
    CustomString * username = new CustomString((std::string)username_val);
    
    std::vector<CustomObject *> returnValues = {dynamic_cast<CustomObject*>(username)};
    
    Message replyMessage;
    
    replyMessage.setSocketAddress(messageParamters.getSocketAddress());
    
    marshal(replyMessage, returnValues);
    
    return replyMessage;
}


