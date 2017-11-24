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
#include <fstream>

Message::Message() :headerCount(4){}


Message::Message(const Message& other)
    : MarshalledMessage((MarshalledMessage)other), headerCount(4){
    
    this->type = other.type;
    this->rpcRequestID = other.rpcRequestID;
    this->rpcOperation = other.rpcOperation;
    this->packetID = other.packetID;
    this->sAddress = other.sAddress;
}

Message::Message(const MarshalledMessage& other) 
    : MarshalledMessage(other), headerCount(4) {}


Message& Message::operator=(const Message& other) {
    
    MarshalledMessage::operator=((MarshalledMessage)other);
    this->type = other.type;
    this->rpcRequestID = other.rpcRequestID;
    this->rpcOperation = other.rpcOperation;
    this->packetID = other.packetID;
    this->sAddress = other.sAddress;
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

int Message::getHeaderSize() const {
    
    return headerCount*4;
    
}
void Message::getMessageWithHeaders(char * mess) const {
    
    const int headersCnt = 4;
    
    CustomInt headers[headersCnt];
    headers[0].setValue((int)type);
    headers[1].setValue(rpcOperation);
    headers[2].setValue(rpcRequestID);
    headers[3].setValue(packetID);
        
    std::string marshalledHeaders = "";
    
    for (int i = 0; i < headersCnt; i++) {
        
        marshalledHeaders += headers[i].marshal();
    }
    
    for (int i = 0; i < headersCnt*4; i++) {
        mess[i] = marshalledHeaders[i];
    }
    
    memcpy(mess + headersCnt*4, message, messageSize);
    
}

void Message::setDestIPAddress(const std::string ipAddress) {

    sAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    sAddress.sin_family = AF_INET;
    // sAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

}

void Message::setSocketAddress(const sockaddr_in & sockAddress) {
    
    sAddress = sockAddress;
}

void Message::setDestPortNumber(const unsigned short &portNumber) {
    
    sAddress.sin_port = htons(portNumber);
}

sockaddr_in Message::getSocketAddress() const {
    
    return sAddress;
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
    startPosition = 0;
    
    for (int i = 0; i < headerCnt; i++) {
        bufferPosition = headers[i].unmarshal(*this, bufferPosition);
    }

        
    startPosition = headerCnt*4;
    
    type = (MessageType)headers[0].getValue();
    rpcOperation = headers[1].getValue();
    rpcRequestID = headers[2].getValue();
    packetID = headers[3].getValue();
    
    // messageSize -= headerCnt * 4;
    
}

std::vector<Message> Message::divide(const size_t & chunkSize) const {
    int packetsNumber = ceil(float(messageSize)/ chunkSize);

    std::vector<Message> dividedMessages;
    
    Message singleMessage;
    singleMessage.setRpcOperation(this->rpcOperation);
    singleMessage.setRpcRequestID(this->rpcRequestID);
    singleMessage.setMessageType(this->type);
    singleMessage.setSocketAddress(this->sAddress);
    
    int messageIndex = 0;
    printf("dividing to %d packets \n", packetsNumber);

        
    for (int order = 1; order <= packetsNumber; order++) {
        
        size_t packetSize = (order == packetsNumber) ? (messageSize - messageIndex) : chunkSize;
        printf("packet %d size %d\n", order, (int)packetSize); 
        singleMessage.createMessage(packetSize);
        
        for(int i = 0; i < packetSize; i++) {
            singleMessage[i] = message[messageIndex++];
        }
        
        singleMessage.setPacketID(order);
        singleMessage.setRpcOperation(this->rpcOperation);
        singleMessage.setRpcRequestID(this->rpcRequestID);
        dividedMessages.push_back(singleMessage);
    }
    
    // std::ofstream afile("after_divide.png", std::ofstream::binary);

    // for(int i = 0; i < dividedMessages.size();++i){
    //     afile.write(dividedMessages[i].message+16, dividedMessages[i].messageSize);
    // }

    // afile.close();

    return dividedMessages;
}

void Message::combine(std::vector<Message> messages)
{
    size_t packetsSize = 0;
    
    for(int i = 0; i < messages.size(); ++i) {
        printf("msg %d size %d\n", i, messages[i].messageSize);
        packetsSize += messages[i].messageSize - messages[i].getHeaderSize();
    }
    
    message = new char[packetsSize];
    messageSize = packetsSize;

    printf("\n");
    printf("p1 startPosition %d, p2 sp %d\n", messages[0].startPosition, messages[1].startPosition);
    for (int i = 0; i < 1000; ++i)
    {
        printf("%d ", (int) messages[0][i]);
    }

    printf("\n");

    printf("Message Size: %d\n", (int)messages[1].getMessageSize());
    for (int i = 0; i < 1000; ++i)
    {
        printf("%d ", (int)messages[1][i]);
    }
    printf("\n");

    for (int i = 0; i < 504; ++i)
    {
        printf("%d ", (int)messages[2][i]);
    }
    printf("\n\n\n");

    int offset = 0;
    for (int i = 0; i < messages.size(); ++i)
    {
        char* m = messages[i].message + 16;
        // memcpy(message + offset, messages[i].message + messages[i].startPosition, messages[i].messageSize);
         memcpy(message + offset, m, messages[i].messageSize - messages[i].getHeaderSize());
        // memcpy(message + offset, messages[i].message + 16, messages[i].messageSize);
        offset += messages[i].messageSize - messages[i].getHeaderSize();
    }
    for (int i = 0; i < 2520; ++i)
    {
        printf("%d ", message[i]);
    }
    printf("\n");
    
    this->setRpcOperation(messages[0].rpcOperation);
    this->setRpcRequestID(messages[0].rpcRequestID);
    this->setMessageType(Reply);
}
