//
//  Message.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//


#include "Message.h"

MessageType Message::getMessageType() {
    return this->type;
}

void Message::setMessageType(const MessageType &type) {
    this->type = type;
}

void Message::setOperationId(int operation) {
    this->operation = operation;
}
