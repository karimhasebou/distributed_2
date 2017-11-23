#ifndef Packet_H
#define Packet_H

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "Message.h"

class Packet {
    
private:
    
    Message message;
    struct sockaddr_in sAddress;
    
public:
    
    Packet(){}
    
    Packet(std::string ipAddress,
             unsigned short portNumber);
    
    void setPacketMessage(Message&);
    void setDestIPAddress(const std::string);
    void setDestPortNumber(const unsigned short& portNumber);
    void setSocketAddress(const sockaddr_in &);
    
    Message& getPacketMessage();
    const Message& getPacketMessage() const;
    sockaddr_in getSocketAddress() const;
};

#endif
