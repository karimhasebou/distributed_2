//
//  AuthenticationServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/24/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RequestHandler.h"
#include "Database/DatabaseHandler.h"
#include "RPC/RpcStub.h"

int main() {
    
    using namespace std::chrono;
    
    readDatabase();

    addRequestHandler(1, login);
    addRequestHandler(2, getUsersIPAddress);
    addRequestHandler(3, getUsername);
//    addRequestHandler(8, getUserNamefromIP);
    
    
    initRequestHandler(63000);

    std::this_thread::sleep_for(std::chrono::seconds(10000));
    puts("server shutting down...\n");
    
    shutdown();
    
    std::this_thread::sleep_for(std::chrono::seconds(100));
    puts("server shut down...\n");

    
}
