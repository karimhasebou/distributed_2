//
//  Message.h
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef Message_hpp
#define Message_hpp

enum MessageType {
    Request,
    Reply
};

#include "MarshalledMessage.h"
#include <iostream>

class Message : public MarshalledMessage {
    
private:
    MessageType type;
    int operation;
    
public:
    Message(){};
    
    MessageType getMessageType();
    void setMessageType(const MessageType&);
    void setOperationId(int oper);
};

#endif /* Message_hpp */

// each class has their own marshalling logic
