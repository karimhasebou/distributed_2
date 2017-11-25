//
//  AuthenticationServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/24/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RequestHandler.h"
#include "RPCStub.h"

int main() {
    
    // DatabaseManager.h
    // DatabaseManager.cpp
    
    // InitializeDatabase , read file, put in a map
    // int lookInDatabase(std::string, std::sting )
    // 1 -> sucess, 2 -> passward incorrect 3-> username not found
    addRequestHandler(1, login);
    addRequestHandler(2, getIPAddress);
    
    initRequestHandler(64000);
    
    
    
}
