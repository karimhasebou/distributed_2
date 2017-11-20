#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Datagram.h"

class UDPSocket {
    
private:
    void fillAddress(struct sockaddr_in&, unsigned short);
    int socketDesc;

public:
    UDPSocket();
    ~UDPSocket();
    
    void bind(unsigned short);

    int sendDatagram(Datagram&);
    int recieveDatagram(Message &);
    
    void shutdown();
    void setTimeOut(int);

};

#endif
