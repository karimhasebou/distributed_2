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
    Last,
    Request,
    Reply
};

#include "../Marshalling/MarshalledMessage.h"
#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>

class Message : public MarshalledMessage {
    
private:
    MessageType type;
    int rpcOperation;
    int rpcRequestID;
    int packetID;
    const int headerCount;
    sockaddr_in sAddress;
    
public:
    Message();
    Message(const Message&);
    Message(const MarshalledMessage&);
    Message& operator=(const Message&);
    
    MessageType getMessageType() const;
    int getRpcOperation() const;
    int getRpcRequestId() const;
    int getPacketID() const;
    int getHeaderSize() const;
    void getMessageWithHeaders(char *) const;
    
    bool isAcknowledgement() const;
    
    void setDestIPAddress(const std::string);
    void setDestPortNumber(const unsigned short& portNumber);
    void setSocketAddress(const sockaddr_in &);
    
    sockaddr_in getSocketAddress() const;
    
    void setMessageType(const MessageType&);
    void setRpcOperation(int);
    void setRpcRequestID(int);
    void setPacketID(int);
    
    void extractHeaders();
    
    std::vector<Message> divide(const size_t&) const;
    void combine(std::vector<Message>);
};

#endif /* Message_hpp */

// each class has their own marshalling logic
