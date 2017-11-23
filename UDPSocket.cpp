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

int UDPSocket::getSockDesc()
{
    return this->socketDesc;
}

void UDPSocket::bind(unsigned short portNumber){

    sockaddr_in address;
    fillAddress(address, portNumber);
    
    if (portNumber == 0) {
        
        int randomSocketDesr = socket(AF_INET, SOCK_DGRAM, 0);
        
        ::bind(randomSocketDesr, (struct sockaddr*)&address, sizeof address);
        
        socklen_t addressLength = sizeof address;
        
        getsockname(randomSocketDesr, (struct sockaddr *)&address, &addressLength);
        
        int randomPort = ntohs(address.sin_port);
                
        close(randomSocketDesr);
        
        sockaddr_in nawawy;
        
        fillAddress(nawawy, randomPort);
        
        ::bind(socketDesc, (struct sockaddr*)&address, sizeof nawawy);
        
    } else {
        
        ::bind(socketDesc, (struct sockaddr*)&address, sizeof address);

    }
    
    printf("Created New Socket, Port Number : %d\n", (int)ntohs(address.sin_port));

}


int UDPSocket::sendPacket(const Message& sentMessage){
    
    sockaddr_in destAddress = sentMessage.getSocketAddress();
    
    size_t messageWithHeaderLen = sentMessage.getHeaderSize()
                + sentMessage.getMessageSize();
    
    char * messageWithHeader = new char[messageWithHeaderLen];
    
    sentMessage.getMessageWithHeaders(messageWithHeader);
            
    int status = (int)sendto(socketDesc,
                             messageWithHeader,
                             messageWithHeaderLen, 0,
                             (sockaddr *) & destAddress,
                             sizeof(destAddress));
    
    sockaddr_in address;

       socklen_t addressLength = sizeof address;

       getsockname(this->socketDesc, (struct sockaddr *)&address, &addressLength);
    
       printf("Sending from port:  %d to port %d\n", ntohs(address.sin_port), ntohs(destAddress.sin_port));
    
    return status;
}


int UDPSocket::recievePacket(Message & receivedMessage)
{
    sockaddr_in senderAddress;
    socklen_t senderLen = sizeof(senderAddress);
    
    size_t maxLength = 66;
    receivedMessage.createMessage(maxLength);

    int status = (int)recvfrom(this->socketDesc,
                               receivedMessage.getMessageBuffer(),
                               maxLength, MSG_WAITALL,
                               (sockaddr *) &senderAddress, &senderLen);
    
    printf("Received from port number : %d\n", (int)ntohs(senderAddress.sin_port));
    
    receivedMessage.setSocketAddress(senderAddress);
    
    receivedMessage.extractHeaders();
    
    printf("Packet ID : %d, Request ID: %d, RPCoperation: %d, Type: %d \n", receivedMessage.getPacketID(), receivedMessage.getRpcRequestId(), receivedMessage.getRpcOperation(), receivedMessage.getMessageType());
    
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

// remove this function 

sockaddr_in UDPSocket::getSocketAddress() {
    
    sockaddr_in myaddress;
    socklen_t size = sizeof(myaddress);
    getpeername(this->socketDesc, (struct sockaddr *)&myaddress, &size);
    
    myaddress.sin_addr.s_addr = htonl(INADDR_ANY);
    
    return myaddress;
}
