#include "UDPSocket.h"
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <cstring>
using namespace std;

UDPSocket::UDPSocket(){
    
    this->socketDesc = socket(AF_INET, SOCK_DGRAM, 0);
}

int UDPSocket::sendDatagram(Datagram& datagram){
    
    const char* buff = datagram.message.c_str();
    socklen_t slen = sizeof(datagram.sAddress);
    int status = (int)sendto(socketDesc, buff, datagram.length + 1, 0, (sockaddr *) & datagram.sAddress, slen); //here
    
    return status;
}


void UDPSocket::bind(unsigned short portNumber){
    sockaddr_in address;
    fillAddress(address, portNumber);
    ::bind(socketDesc, (struct sockaddr*)&address, sizeof address);
}

Datagram UDPSocket::recieveDatagram()
{
    sockaddr_in socketAddress;
    socklen_t clientLen = sizeof(socketAddress); ///here
    char buff[100];
    size_t maxLen = 100;
 
    int status = (int)recvfrom(this->socketDesc, buff, maxLen, MSG_WAITALL, (sockaddr *) &socketAddress, &clientLen); //here
    if (status == -1)
        strcpy(buff, "Timeout...");
    string message(buff);
    Datagram datagram(message , message.length(), socketAddress);
    datagram.status = status;
    
    return datagram;
    
}

void UDPSocket::fillAddress(struct sockaddr_in& socket, unsigned short port)
{
    socket.sin_family = AF_INET;
    socket.sin_port = htons(port);
    socket.sin_addr.s_addr = htonl(INADDR_ANY);
}

void UDPSocket::shutdown() {
    
    close(socketDesc);

}

UDPSocket::~UDPSocket() {

}

void UDPSocket::setTimeOut(int time)
{
    struct timeval tv;
    tv.tv_sec = time;
    tv.tv_usec = 0;
    setsockopt(this->socketDesc, SOL_SOCKET, SO_RCVTIMEO, (const char*) &tv, sizeof(struct timeval));
}


