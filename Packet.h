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
    
    void setMessage(Message&);
    void setDestIPAddress(const std::string);
    void setDestSocketAddress(const sockaddr_in &);
    void setDestPortNumber(const unsigned short& portNumber);
    
    Message& getMessage();
    const Message& getMessage() const;
    sockaddr_in getDestSocketAddress() const;
};

#endif
