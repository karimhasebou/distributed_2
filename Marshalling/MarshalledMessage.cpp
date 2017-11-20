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
    
    this->messageSize = other.messageSize;
    this->message = new char[messageSize];
    this->startPosition = 0;
    
    for (int i = 0; i < messageSize; i++) {
        this->message[i] = other.message[i];
    }
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

char * MarshalledMessage::getMessage() {
    return message;
}

size_t MarshalledMessage::getMessageSize() {
    return messageSize;
}

void MarshalledMessage::createMessage(size_t messageSize) {
    this->message = new char[messageSize];
    this->messageSize = messageSize;
}

char& MarshalledMessage::operator[](int index) {
    if (index + startPosition >= messageSize) {
        throw("Bad aceess");
    }
    
    return this->message[index + startPosition];
}
