#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Datagram.h"

class UDPSocket {

public:
    UDPSocket();
    int sendDatagram(Datagram&);
    void bind(unsigned short);
    Datagram recieveDatagram();
    void shutdown();
    void setTimeOut(int);
    ~UDPSocket();

private:
    void fillAddress(struct sockaddr_in&, unsigned short);
    int socketDesc;
    
};

#endif
