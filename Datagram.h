#ifndef DATAGRAM_H
#define DATAGRAM_H

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

class Datagram {
    
public:
    
    string message;
    size_t length;
    
    // Message -> get message returns char * s 
    struct sockaddr_in sAddress;
    string ipAddress;
    int status;
    
    Datagram(const string& mess,
             const size_t& len,
             string ipAddress,
             unsigned short portNumber)
    :message(mess) , length(len) {
        
        sAddress.sin_family = AF_INET;
        sAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
        sAddress.sin_port = htons(portNumber);
        this->ipAddress = ipAddress;
        status = 0;
    }
    
    Datagram(const string& mess,
             const size_t& len,
             struct sockaddr_in addr)
    :message(mess), length(len), sAddress(addr) {}
    
    void updateMessage(const string& newMessage) {
        message = newMessage;
        length = (size_t)newMessage.length() + 1;
    }       
};

#endif
