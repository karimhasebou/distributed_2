#ifndef DATAGRAM_H
#define DATAGRAM_H

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

class Datagram {
    
public:
    
    char *message;
    size_t length;
    struct sockaddr_in sAddress;
    int status;
    
    Datagram()
    {

    }

    Datagram(char mess[],
             const size_t& len,
             string ipAddress,
             unsigned short portNumber)
    :message(mess) , length(len) {
        
        sAddress.sin_family = AF_INET;
        sAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
        sAddress.sin_port = htons(portNumber);
        status = 0;
    }
    
    Datagram(char mess[],
             const size_t& len,
             struct sockaddr_in addr)
    :message(mess), length(len), sAddress(addr) {}
    
};

#endif
