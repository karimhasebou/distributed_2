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

#define IMG_DIR ""
#define IMG_LIST_FILE ""
#define AUTHORIZED_USERS ""

enum LoginStatus {
    loginSucess = 1,
    wrongPassword = 2,
    wrongUsername = 3
};

namespace server{
    typedef struct{
        char *content;
        size_t length;
    } Image;

    typedef struct{
        std::string username;
        int viewCount;
    } DBEntry;

    //utilities
    std::map<std::string, int> readAuthorizedUsersDB();
    void writeDB(std::map<std::string, int> list);

    std::vector<std::string> listImages();
    std::set<std::string> getAuthorizedUsers(std::string filePath);
    
    void server::stegUserList(std::string imagename);
    void unstegUserList(std::string filePath);
    std::string getPath(std::string imgName);

    Image getImage(std::string imgName);
    std::vector<std::string> getAccessibleImages(std::string username);

    bool canUpdateCount(std::string imgName, 
        std::string username);
    bool updateCount(std::string imgName, 
        std::string username, int count);

    // returns empty string if 
    // no user is currently logged in
    std::string getLoggedUsername();
}

namespace client {
    
    LoginStatus login(std::string, std::string);
    std::vector<std::string> getIPAddress();
}

namespace authserver {
    LoginStatus login(std::string, std::string);
    std::vector<std::string> getIPAddress(const std::string&);
    std::string getUsername(std::string);
}


#endif /* RpcCalls_h */
