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


int UDPSocket::sendPacket(const Packet& packet){
    
    sockaddr_in destAddress = packet.getSocketAddress();
        
    int status = (int)sendto(socketDesc,
                             packet.getPacketMessage().getMessageBuffer(),
                             packet.getPacketMessage().getMessageSize(), 0,
                             (sockaddr *) & destAddress,
                             sizeof(destAddress));
        
    return status;
}


int UDPSocket::recievePacket(Packet & packet)
{
    sockaddr_in myaddress;
    socklen_t length = sizeof myaddress;
    getsockname(this->socketDesc, (struct sockaddr *) &myaddress, &length);
    
    printf("the port number is %d\n", (int)ntohs(myaddress.sin_port));
    
    sockaddr_in senderAddress;
    socklen_t senderLen = sizeof(senderAddress);
    
    size_t maxLength = 4096;
    packet.getPacketMessage().createMessage(maxLength);

    int status = (int)recvfrom(this->socketDesc,
                               packet.getPacketMessage().getMessageBuffer(),
                               maxLength, MSG_WAITALL,
                               (sockaddr *) &senderAddress, &senderLen);
    
    packet.setSocketAddress(senderAddress);
                
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

sockaddr_in UDPSocket::getSocketAddress() {
    
    sockaddr_in myaddress;
    socklen_t size = sizeof(myaddress);
    getpeername(this->socketDesc, (struct sockaddr *)&myaddress, &size);
    
    myaddress.sin_addr.s_addr = htonl(INADDR_ANY);
    
    return myaddress;
}
