//
//  Message.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Message.h"
#include "CustomObjects/CustomInt.h"

Message::Message(const Message& other) {
    
    this->messageSize = other.messageSize;
    this->message = new char[this->messageSize];
    
    for (int i = 0; i < this->messageSize; i++) {
        this->message[i] = other.message[i];
    }
}

Message::Message(const MarshalledMessage& other) 
    : MarshalledMessage(other) {}


Message& Message::operator=(const Message& other) {
    
    this->messageSize = other.messageSize;
    this->message = new char[this->messageSize];
    
    for (int i = 0; i < this->messageSize; i++) {
        this->message[i] = other.message[i];
    }
    
    return *this;
}


MessageType Message::getMessageType() {
    return this->type;
}

void Message::setMessageType(const MessageType &type) {
    this->type = type;
}

void Message::setRpcOperation(int operation) {
    this->rpcOperation = operation;
}

void Message::setRpcRequestID(int rpcid) {
    this->rpcRequestID = rpcid;
}

void Message::extractHeaders() {
    
    CustomInt headers[3];

    for (int i = 0; i < 3; i++) {
        startPosition = headers[i].unmarshal(message, startPosition);
    }
    
    type = (MessageType)headers[0].getValue();
    rpcOperation = headers[1].getValue();
    rpcRequestID = headers[2].getValue();
    
}
