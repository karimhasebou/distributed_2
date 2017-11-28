//
//  RpcCallsAuthServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RpcCalls.h"
#include "../Database/DatabaseHandler.h"

LoginStatus authserver::login(std::string username, std::string password) {

    return (LoginStatus)checkInDatabase(username, password);

}

std::map<std::string, std::string> authserver::getUsersIpAddress(const std::string & senderAddress)
{
    std::map<std::string, std::string> onlineList = getOnlinePeers();

    onlineList.erase(onlineList.find(senderAddress));

    return onlineList;
}

std::string authserver::getUsername(std::string IPAddress)
{
    return getIPfromUser(IPAddress);
}





