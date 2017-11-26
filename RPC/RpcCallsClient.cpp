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
const unsigned short serverPort = 64000;

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

std::vector<std::string> client::getAccessibleImages(std::string username, std::string ipAddress)
{
    Message rpcCallMessage;
    MySocket rpcSocket;

    std::vector<std::string> images;

    rpcCallMessage.setDestIPAddress(ipAddress);
    rpcCallMessage.setDestPortNumber(serverPort);

    CustomString * usernameString = new CustomString(username);
        
    std::vector<CustomObject * > parameters = {dynamic_cast<CustomObject *>(usernameString)};

    marshal(rpcCallMessage, parameters);

    rpcCallMessage.setMessageType(Request);
    rpcCallMessage.setRpcOperation(4);
        
        
    Message rpcReplyMessage = rpcSocket.callRPC(rpcCallMessage);

    std::vector<CustomObject *> returnValues = {new CustomVector()};
        
    unmarshal(rpcReplyMessage, returnValues);
        
    CustomVector* returnVector = dynamic_cast<CustomVector *>(returnValues[0]);

    std::vector<std::string> tmp = returnVector->getValue();

    return tmp;
}

Image client::getImage(std::string imageName, std::string ipAddress)
{
    Message rpcCallMessage;
    MySocket rpcSocket;

    rpcCallMessage.setDestIPAddress(ipAddress);
    rpcCallMessage.setDestPortNumber(serverPort);

    CustomString * image_name = new CustomString(imageName);
        
    std::vector<CustomObject * > parameters = {dynamic_cast<CustomObject *>(image_name)};

    marshal(rpcCallMessage, parameters);

    rpcCallMessage.setMessageType(Request);
    rpcCallMessage.setRpcOperation(5);
        
        
    Message rpcReplyMessage = rpcSocket.callRPC(rpcCallMessage);



    std::vector<CustomObject *> returnValues = {new CustomString()};
        
    unmarshal(rpcReplyMessage, returnValues);
        
    CustomString* returnVector = dynamic_cast<CustomString *>(returnValues[0]);

    std::string imageString = returnVector->getValue();

    Image img;

    img.length = imageString.length();
    img.content = new char[img.length];

    for (int i = 0; i < img.length; i++)
        img.content[i] = imageString[i];

    std::string imageFilePath = "../DownloadedImages/" + imageName;
        
    std::ofstream outfile(imageFilePath , std::ofstream::binary);
        
    printf("length of image %s" , img.length);
    outfile.write(img.content, img.length);

    return img;
}
