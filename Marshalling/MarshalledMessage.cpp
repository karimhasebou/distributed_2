//
//  MarshallingMessage.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "MarshalledMessage.h"
#include <exception>

MarshalledMessage::MarshalledMessage(const MarshalledMessage& other) {
    
    copyMessageArray(other.message, other.messageSize);
    
}

MarshalledMessage::MarshalledMessage() {
    
    this->message = NULL;
    this->startPosition = 0;
}

MarshalledMessage::~MarshalledMessage() {
    
    if (this->message != NULL) {
        delete this->message;
    }
}

char * MarshalledMessage::getMessageContent() const {
    
    return message;
    
}

size_t MarshalledMessage::getMessageSize() const{
    
    return messageSize;
    
}

void MarshalledMessage::createMessage(size_t messageSize) {
    
    this->message = new char[messageSize];
    this->messageSize = messageSize;
    
}
//
//void MarshalledMessage::fillMessage(char * message) {
//    
//    strncpy(this->message, message, this->messageSize);
//
//}

char& MarshalledMessage::operator[](int index) {
    
    if (index + startPosition >= messageSize) {
        throw("Bad aceess");
    }
    
    return this->message[index + startPosition];
}

void MarshalledMessage::copyMessageArray(char * message, size_t messageSize) {
    
    this->messageSize = messageSize;
    this->message = new char[messageSize];
    this->startPosition = 0;
    
    for (int i = 0; i < messageSize; i++) {
        this->message[i] = message[i];
    }
}
