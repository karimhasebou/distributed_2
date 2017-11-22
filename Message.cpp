//
//  Message.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Message.h"
#include <math.h>
#include "CustomObjects/CustomInt.h"

Message::Message(const Message& other) {
    
    copyMessageArray(other.message, other.messageSize);
    
}

Message::Message(const MarshalledMessage& other) 
    : MarshalledMessage(other) {}


Message& Message::operator=(const Message& other) {
    
    copyMessageArray(other.message, other.messageSize);
    
    return *this;
}


MessageType Message::getMessageType() const {
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
    
    CustomInt headers[4];

    for (int i = 0; i < 4; i++) {
        startPosition = headers[i].unmarshal(message, startPosition);
    }
    
    type = (MessageType)headers[0].getValue();
    rpcOperation = headers[1].getValue();
    rpcRequestID = headers[2].getValue();
    packetID = headers[3].getValue();
    
}

std::vector<Message> Message::divide(const size_t & chunkSize) const {
    
    int packetsNumber = ceil(float(messageSize)/ chunkSize);

    std::vector<Message> packets;
    
    Message packet;
    packet.setRpcOperation(this->rpcOperation);
    packet.setRpcRequestID(this->rpcRequestID);
    packet.setMessageType(this->type);
    
    int messageIndex = 0;
        
    for (int order = 1; order <= packetsNumber; order++) {
        
        size_t packetSize = (order == packetsNumber) ? (messageSize - messageIndex) : chunkSize;
        
        packet.createMessage(packetSize);
        
        for(int i = 0; i < packetSize; i++) {
            packet[i] = message[messageIndex++];
        }
        
        packet.setPacketID(order);
        packets.push_back(packet);
    }
    
    return packets;
}

void Message::combine(std::vector<Message> messages)
{
    size_t packets_size = 0;
    
    for(int i = 0; i < messages.size(); ++i) {
        
        packets_size += messages[i].messageSize;
    }
    
    
    message = new char[packets_size];
    int offset = 0;
    for (int i = 0; messages.size(); ++i)
    {
        memcpy(message + offset, messages[i].message, messages[i].messageSize);
        offset += messages[i].messageSize;
    }
}
