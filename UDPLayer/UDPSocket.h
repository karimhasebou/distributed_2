#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../UDPLayer/Message.h"

class UDPSocket {
    
private:
    void fillAddress(struct sockaddr_in&, unsigned short);
    int socketDesc;

public:
    UDPSocket();
    ~UDPSocket();
    
    void bind(unsigned short);

    int sendPacket(const Message&);
    int recievePacket(Message &);
    
    void shutdown();
    void setTimeOut(int);
    
    sockaddr_in getSocketAddress();
    int getSockDesc();

};

#endif
