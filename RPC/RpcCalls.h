//
//  RpcCalls.h
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef RpcCalls_h
#define RpcCalls_h

#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <set>
#include <map>
#include "../CustomObjects/CustomObject.h"
#include "../CustomObjects/CustomInt.h"
#include "../CustomObjects/CustomString.h"
#include "../CustomObjects/CustomVector.h"
#include "../CustomObjects/CustomBool.h"
#include "../Marshalling/MarshalledMessage.h"
#include "../Marshalling/MarshallingManager.h"
#include "../UDPLayer/Message.h"

enum LoginStatus {
    loginSucess = 1,
    wrongPassword = 2,
    wrongUsername = 3
};

typedef struct{
    char * content;
    size_t length;
} Image;

namespace server{

    Image getImage(std::string);
    std::vector<std::string> getAccessibleImages(const std::string&);
    bool canUpdateCount(std::string, std::string);
    bool updateCount(std::string, std::string, int);
    std::string pingUser();     //change
}

namespace client {
    
    LoginStatus login(std::string, std::string);
    std::vector<std::string> getIPAddress();
    Image getImage(std::string, std::string);
    std::vector<std::string> getAccessibleImages(std::string, std::string);
    bool updateCount(std::string, std::string, int);
    std::string getUsername(std::string);
    

}

namespace authserver {
    LoginStatus login(std::string, std::string);
    std::vector<std::string> getIPAddress(const std::string&);
    std::string getUsername(std::string);
}


#endif /* RpcCalls_h */
