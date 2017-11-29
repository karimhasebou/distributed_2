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
#include "../CustomObjects/CustomMap.h"
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

Message getUsersIPAddress(Message& messageParamters) {
    
    struct in_addr senderIPAddress = messageParamters.getSocketAddress().sin_addr;
    char senderAddressChar[15];
    inet_ntop(AF_INET, &senderIPAddress, senderAddressChar , 15);
    std::string senderAddressString(senderAddressChar);
//    std::map <std::string, std::string> bs = authserver::getUsersIpAddress(senderAddressString);
//    CustomMap * usersIpAddress;
    CustomMap * usersIpAddress = new CustomMap(authserver::getUsersIpAddress(senderAddressString));
    
    std::vector<CustomObject*> returnValues = {dynamic_cast<CustomObject*>(usersIpAddress)};
    
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


Message getUserNamefromIP(Message& messageParamters)
{
    std::vector<CustomObject *> parameters = {new CustomString()};
    
    unmarshal(messageParamters, parameters);
    
    std::string username = (dynamic_cast<CustomString *>(parameters[0]))->getValue();

    std::string ipAddress_val = authserver::getUsername(username);
    printf("\t username %s got ip %s\n", username.c_str(), ipAddress_val.c_str());
    
    CustomString * ipAddress = new CustomString((std::string)ipAddress_val);
    
    std::vector<CustomObject *> returnValues = {dynamic_cast<CustomObject*>(ipAddress)};
    
    Message replyMessage;
    
    replyMessage.setSocketAddress(messageParamters.getSocketAddress());
    
    marshal(replyMessage, returnValues);
    
    return replyMessage;
}
