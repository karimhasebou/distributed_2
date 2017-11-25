//
//  RpcStubAuthServer.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/25/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "RpcStub.h"
#include "RpcCalls.h"
#include <vector>
#include "../Marshalling/MarshallingManager.h"
#include "../Marshalling/MarshalledMessage.h"
#include "../CustomObjects/CustomInt.h"
#include "../CustomObjects/CustomString.h"
#include "../CustomObjects/CustomObject.h"
#include "../CustomObjects/CustomVector.h"
#include "../CustomObjects/CustomBool.h"
#include "../UDPLayer/MySocket.h"

Message login(Message& messqgeParamters) {
    
    std::vector<CustomObject *> parameters = {new CustomString(), new CustomString()};
    
    unmarshal(messqgeParamters, parameters);
    
    std::string username = (dynamic_cast<CustomString *>(parameters[0]))->getValue();
    
    std::string password = (dynamic_cast<CustomString *>(parameters[1]))->getValue();

    bool status = authserver::login(username, password);

    CustomBool * loginStatus = new CustomBool(status);
    
    std::vector<CustomObject *> returnValues = {dynamic_cast<CustomObject*>(loginStatus)};
    
    Message replyMessage;
    
    marshal(replyMessage, returnValues);
    
    return replyMessage;
    
}
