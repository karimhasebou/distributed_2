//
//  RpcCallsClient.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RpcCalls.h"
#include "../UDPLayer/MySocket.h"
#include <errno.h>
#include <unistd.h>

std::string authServerIP = "127.0.0.1";
const unsigned short authServerPort = 63000;

LoginStatus client::login(std::string username, std::string password) {
    
    CustomString * usernameString = new CustomString(username);
    CustomString * passwordString = new CustomString(password);
    
    std::vector<CustomObject * > parameters = {dynamic_cast<CustomObject *>(usernameString),
        dynamic_cast<CustomObject *>(passwordString)};
    
    Message rpcCallMessage;
    rpcCallMessage.setDestIPAddress(authServerIP);
    rpcCallMessage.setDestPortNumber(authServerPort);
    
    marshal(rpcCallMessage, parameters);
        
    rpcCallMessage.setRpcOperation(1);
    rpcCallMessage.setRpcRequestID(7);
    rpcCallMessage.setMessageType(Request);
    
    MySocket rpcSocket;
    
    Message rpcReplyMessage =  rpcSocket.callRPC(rpcCallMessage);
    
    std::vector<CustomObject *> returnValues = {new CustomInt()};
    
    unmarshal(rpcReplyMessage, returnValues);
    
    CustomInt * loginStatus = dynamic_cast<CustomInt *>(returnValues[0]);
    
    return (LoginStatus)loginStatus->getValue();
    
}

std::vector<std::string> client::getIPAddress()
{
    Message rpcCallMessage;
    rpcCallMessage.setDestIPAddress(authServerIP);
    rpcCallMessage.setDestPortNumber(authServerPort);
    
    rpcCallMessage.createMessage(0);
    rpcCallMessage.setMessageType(Request);
    rpcCallMessage.setRpcOperation(2);
    
    MySocket rpcSocket;
    
    Message rpcReplyMessage = rpcSocket.callRPC(rpcCallMessage);
    
    std::vector<CustomObject* > returnValues = {new CustomVector()};
    
    unmarshal(rpcReplyMessage, returnValues);
    
    CustomVector * ipList = dynamic_cast<CustomVector *>(returnValues[0]);
    
    return ipList->getValue();
//    std::vector<std::string> ipAddresses = ipList->getValue();
//    
//    sockaddr_in myAddressIn;
//    myAddressIn.sin_addr.s_addr = htonl(INADDR_ANY);
//    in_addr myAddress = myAddressIn.sin_addr;
//    
//    char myIPChar[3 * 4 + 3];
//    inet_ntop(AF_INET, &myAddress, myIPChar, 3 * 4 + 3 );
//    
//    printf("My IP adrress is %s\n", myIPChar);
//
//    std::string myIPString(myIPChar);
//    
//    for ( int i = 0; i < ipAddresses.size(); ++i)
//    {
//        if(ipAddresses[i] == myIPString) {
//            ipAddresses.erase(ipAddresses.begin() + i);
//        }
//    }
//    
//    return ipAddresses;
}

std::string client::getUsername(std::string IPAddr)
{
    CustomString * IPAddress = new CustomString(IPAddr);
    
    std::vector<CustomObject * > parameters = {dynamic_cast<CustomObject *>(IPAddress)};

    Message rpcCallMessage;
    rpcCallMessage.setDestIPAddress(authServerIP);
    rpcCallMessage.setDestPortNumber(authServerPort);
    
    marshal(rpcCallMessage, parameters);
    
    rpcCallMessage.setRpcOperation(3);
    rpcCallMessage.setRpcRequestID(7);
    rpcCallMessage.setMessageType(Request);
    
    MySocket rpcSocket;
    
    Message rpcReplyMessage =  rpcSocket.callRPC(rpcCallMessage);
    
    std::vector<CustomObject *> returnValues = {new CustomString()};
    
    unmarshal(rpcReplyMessage, returnValues);
    
    CustomString * username = dynamic_cast<CustomString *>(returnValues[0]);
    
    return username->getValue();


    
}
