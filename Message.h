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
    Acknowledgement,
    Request,
    Reply
};

#include "Marshalling/MarshalledMessage.h"
#include <iostream>

class Message : public MarshalledMessage {
    
private:
    MessageType type;
    int rpcOperation;
    int rpcRequestID;
    
public:
    Message(){};
    Message(const Message&);
    Message(const MarshalledMessage&);
    Message& operator=(const Message&);
    MessageType getMessageType();
    void setMessageType(const MessageType&);
    void setRpcOperation(int);
    void setRpcRequestID(int);
    
    void extractHeaders();
};

#endif /* Message_hpp */

// each class has their own marshalling logic
