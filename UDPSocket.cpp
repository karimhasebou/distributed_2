#include "UDPSocket.h"
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <cstring>
using namespace std;

UDPSocket::UDPSocket(){
    
    this->socketDesc = socket(AF_INET, SOCK_DGRAM, 0);
}

UDPSocket::~UDPSocket() {
    
}

void UDPSocket::bind(unsigned short portNumber){
    
    sockaddr_in address;
    fillAddress(address, portNumber);
    ::bind(socketDesc, (struct sockaddr*)&address, sizeof address);
    
}


int UDPSocket::sendDatagram(Datagram& datagram){
    
    int status = (int)sendto(socketDesc,
                             datagram.getMessage().getMessage(),
                             datagram.getMessage().getMessageSize(), 0,
                             (sockaddr *) & datagram.getDestSocketAddress(),
                             sizeof(datagram.getDestSocketAddress()));
    
    return status;
}


int UDPSocket::recieveDatagram(Message & message)
{
    sockaddr_in socketAddress;
    socklen_t clientLen = sizeof(socketAddress);
    
    size_t maxLength = 4096;
    message.createMessage(maxLength);

 
    int status = (int)recvfrom(this->socketDesc,
                               message.getMessage(), maxLength,
                               MSG_WAITALL,
                               (sockaddr *) &socketAddress, &clientLen);
  
//    if (status == -1)
//        strcpy(buff, "Timeout...");
    
    message.extractHeaders();
            
    return status;
    
}

void UDPSocket::shutdown() {
    
    close(socketDesc);

}

void UDPSocket::setTimeOut(int time)
{
    struct timeval tv;
    tv.tv_sec = time;
    tv.tv_usec = 0;
    setsockopt(this->socketDesc, SOL_SOCKET, SO_RCVTIMEO, (const char*) &tv, sizeof(struct timeval));
}

void UDPSocket::fillAddress(struct sockaddr_in& socket, unsigned short port)
{
    socket.sin_family = AF_INET;
    socket.sin_port = htons(port);
    socket.sin_addr.s_addr = htonl(INADDR_ANY);
}


