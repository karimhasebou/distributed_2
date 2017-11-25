//
//  MarshallingMessage.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "MarshalledMessage.h"
#include <exception>
#include <cstring>

MarshalledMessage::MarshalledMessage(const MarshalledMessage& other) {
    
    copyMessageArray(other.message, other.messageSize);
    
}

MarshalledMessage::MarshalledMessage() {
    
    this->message = NULL;
}

MarshalledMessage::~MarshalledMessage() {
    
    if (this->message != NULL) {
        delete this->message;
    }
}

MarshalledMessage& MarshalledMessage::operator=(const MarshalledMessage & other) {
    
    copyMessageArray(other.message, other.messageSize);
    return *this;
}

char * MarshalledMessage::getMessageBuffer() const {
    
    return message;
    
}

size_t MarshalledMessage::getMessageSize() const{
    
    return messageSize;
    
}

void MarshalledMessage::createMessage(size_t messageSize) {
    
    this->message = new char[messageSize];
    this->messageSize = messageSize;
    
}

void MarshalledMessage::fillMessage(char * message) {
    
    memcpy(this->message, message, this->messageSize);

}

char& MarshalledMessage::operator[](int index) {
    
    if (index >= messageSize) {
        throw("Bad aceess");
    }
    
    return this->message[index];
}

void MarshalledMessage::copyMessageArray(char * message, size_t messageSize) {
    
    this->messageSize = messageSize;
    this->message = new char[messageSize];
    
    for (int i = 0; i < messageSize; i++) {
        this->message[i] = message[i];
    }
}
