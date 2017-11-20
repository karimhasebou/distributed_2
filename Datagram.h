#ifndef DATAGRAM_H
#define DATAGRAM_H

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "Message.h"

class Datagram {
    
private:
    
    Message message;
    struct sockaddr_in sAddress;
    
public:
    
    Datagram(){}
    
    Datagram(std::string ipAddress,
             unsigned short portNumber);
    
    void setMessage(Message&);
    void setDestIPAddress(const std::string);
    void setDestPortNumber(const unsigned short& portNumber);
    
    Message getMessage();
    sockaddr_in& getDestSocketAddress();
};

#endif
