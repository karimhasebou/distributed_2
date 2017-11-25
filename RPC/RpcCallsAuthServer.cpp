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

std::vector<std::string> authserver::getIPAddress(const std::string& senderAddress)
{
    std::vector<std::string> onlineList = getOnlinePeers();
    
    for (int i = 0; i < onlineList.size(); i++) {
        if (senderAddress == onlineList[i]) {
            onlineList.erase(onlineList.begin() + i);
        }
    }
    
    return onlineList;
}

std::string authserver::getUsername(std::string IPAddress)
{
    return getUserNamefromIP(IPAddress);
}
