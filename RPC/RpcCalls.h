//
//  RpcCalls.h
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef RpcCalls_h
#define RpcCalls_h

#include <string>
#include <vector>
#include "../CustomObjects/CustomObject.h"
#include "../CustomObjects/CustomInt.h"
#include "../CustomObjects/CustomString.h"
#include "../CustomObjects/CustomVector.h"
#include "../CustomObjects/CustomBool.h"
#include "../Marshalling/MarshalledMessage.h"
#include "../Marshalling/MarshallingManager.h"
#include "../UDPLayer/Message.h"

namespace client {
    
    bool login(std::string, std::string);
    std::vector<std::string> getIPAddress();
    
}

namespace authserver {
    bool login(std::string, std::string);
    std::vector<std::string> getIPAddress();
}


#endif /* RpcCalls_h */
