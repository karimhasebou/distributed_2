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
#include "../Database/DatabaseHandler.h"

std::string authServerIP = "10.40.37.203";
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
        
    std::vector<CustomObject *> parameters = {dynamic_cast<CustomObject *>(image_name)};

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
    
    img.content = new char[imageString.length()];

    for (int i = 0; i < imageString.length(); i++)
        img.content[i] = imageString[i];


    return img;
}

bool client::updateCount(std::string imgName, std::string username, int count)
{
   

    CustomString * imageNameString = new CustomString(imgName);
    CustomString * usernameString = new CustomString(username);
    CustomInt * countInt = new CustomInt(count);

    std::vector<CustomObject * > parametersDB = {dynamic_cast<CustomObject *>(usernameString)};
    
    Message dbRpcMessage;
    dbRpcMessage.setDestIPAddress(authServerIP);
    dbRpcMessage.setDestPortNumber(serverPort);
    
    marshal(dbRpcMessage, parametersDB);
        
    dbRpcMessage.setRpcOperation(8);
    dbRpcMessage.setRpcRequestID(7); // ?
    dbRpcMessage.setMessageType(Request);
    
    MySocket rpcSocket;
    
    Message dbReply =  rpcSocket.callRPC(dbRpcMessage);


    std::vector<CustomObject *> returnValuesDB = {new CustomString()};
    
    unmarshal(dbReply, returnValuesDB);
    
    CustomString* returnString = dynamic_cast<CustomString *>(returnValuesDB[0]);

    std::string ipAdd = returnString->getValue();





    std::vector<CustomObject * > parameters = {dynamic_cast<CustomObject *>(imageNameString),
        dynamic_cast<CustomObject *>(usernameString), dynamic_cast<CustomObject *>(countInt)};
    
    Message rpcCallMessage;
    rpcCallMessage.setDestIPAddress(ipAdd);
    rpcCallMessage.setDestPortNumber(serverPort);
    
    // marshal(rpcCallMessage, parameters);
        
    rpcCallMessage.setRpcOperation(6);
    rpcCallMessage.setRpcRequestID(7); // ?
    rpcCallMessage.setMessageType(Request);
        
    Message rpcReplyMessage =  rpcSocket.callRPC(rpcCallMessage);

    // std::vector<CustomObject *> returnValues = {new CustomBool()};
    
    // unmarshal(rpcReplyMessage, returnValues);
    
    // CustomBool* returnVector = dynamic_cast<CustomBool *>(returnValues[0]);

    // return returnVector->getValue();
}


// std::vector<std::string> splitString(std::string sentence)
// {
//   std::stringstream ss;
//   ss<<sentence;
  
//   std::string to;
//   std::vector<std::string> files;

//     while(std::getline(ss,to,'\n')){
//         files.push_back(to);
//     }
    
//     return files;
// }

// std::vector<std::string> listFilesInDir()
// {
//     using namespace std;
//     FILE  *file = popen("ls MyImages", "r");
    
//     int ch;
//     string result;
    
//     do{
//         ch = fgetc(file);
        
//         if(ch == EOF) break;
        
//         result += ch;
//     }while(1);

//     pclose(file);

//     return splitString(result);
// }
