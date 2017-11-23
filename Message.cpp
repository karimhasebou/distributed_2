//
//  Message.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Message.h"
#include <stdio.h>
#include <math.h>
#include "CustomObjects/CustomInt.h"
#include <cstring>

Message::Message(const Message& other) {
    
    copyMessageArray(other.message, other.messageSize);
    this->rpcRequestID = other.rpcRequestID;
    this->rpcOperation = other.rpcOperation;
    this->packetID = other.packetID;
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

int Message::getRpcOperation() const {
    
    return rpcOperation;
    
}

int Message::getRpcRequestId() const {
    
    return rpcRequestID;
}

int Message::getPacketID() const {
    
    return packetID;
    
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

void Message::setPacketID(int packetid) {
    this->packetID = packetid;
}


void Message::extractHeaders() {
    
    const int headerCnt = 4;
    
    CustomInt headers[headerCnt];
    
    int bufferPosition = 0;
    
    std::string shittydebug = "";
    
    for(int i=0; i < messageSize; i++) {
        shittydebug += message[i];
    }
    
    
    for (int i = 0; i < headerCnt; i++) {
        bufferPosition = headers[i].unmarshal(*this, bufferPosition);
    }
    
    startPosition = headerCnt*4;
    
    type = (MessageType)headers[0].getValue();
    rpcOperation = headers[1].getValue();
    rpcRequestID = headers[2].getValue();
    packetID = headers[3].getValue();
    
    messageSize -= headerCnt * 4;
    
}

void Message::fillHeaders() {
    
    const int headersCnt = 4;
    
    CustomInt headers[headersCnt];
    headers[0].setValue((int)type);
    headers[1].setValue(rpcOperation);
    headers[2].setValue(rpcRequestID);
    headers[3].setValue(packetID);
    
    char * messageContent = this->message;
    
    message = new char[messageSize + headersCnt*4];
        
    std::string marshalledHeaders = "";
    
    for (int i = 0; i < headersCnt; i++) {
        
        marshalledHeaders += headers[i].marshal();
    }
    
    for (int i = 0; i < headersCnt*4; i++) {
        message[i] = marshalledHeaders[i];
    }
    
    memcpy(message + headersCnt*4, messageContent, messageSize);
    
    delete [] messageContent;
    
    messageSize += headersCnt*4;
    
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
    for (int i = 0; i < messages.size(); ++i)
    {
        memcpy(message + offset, messages[i].message + startPosition, messages[i].messageSize);
        offset += messages[i].messageSize;
    }
}
