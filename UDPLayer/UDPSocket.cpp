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
    struct in_addr ipAddr = destAddress.sin_addr;
    
    size_t messageWithHeaderLen = sentMessage.getHeaderSize()
                + sentMessage.getMessageSize();
    
    char * messageWithHeader = new char[messageWithHeaderLen];
    
    sentMessage.getMessageWithHeaders(messageWithHeader);
            
    int status = (int)sendto(socketDesc,
                             messageWithHeader,
                             messageWithHeaderLen, 0,
                             (sockaddr *) & destAddress,
                             sizeof(destAddress));
    
    char str[3 * 4 + 3];
    inet_ntop(AF_INET, &ipAddr, str, 3 * 4 + 3 );

    sockaddr_in myAddress;
    socklen_t adrLen = sizeof (myAddress);
    getsockname(this->socketDesc, (struct sockaddr*) &myAddress, &adrLen);
    printf("sending to %s port %d ==> %d status %d errno %d\n"
    , str, ntohs(myAddress.sin_port), ntohs(destAddress.sin_port), status, errno  );
    
    return status;
}


int UDPSocket::recievePacket(Message & receivedMessage)
{
    sockaddr_in senderAddress;
    socklen_t senderLen = sizeof(senderAddress);
    
    size_t maxLength = 1016;
    receivedMessage.createMessage(maxLength);

    sockaddr_in address;
    socklen_t addressLength = sizeof address;
    getsockname(this->socketDesc, (struct sockaddr *)&address, &addressLength);

    int status = (int)recvfrom(this->socketDesc,
                               receivedMessage.getMessageBuffer(),
                               maxLength, MSG_WAITALL,
                               (sockaddr *) &senderAddress, &senderLen);
    
    receivedMessage.setSocketAddress(senderAddress);
    
    receivedMessage.extractHeaders();
    int pid = receivedMessage.getPacketID();
    int rid = receivedMessage.getRpcRequestId();
    int rpco = receivedMessage.getRpcOperation();
    int t = receivedMessage.getMessageType();
    // printf("Packet ID : %d, Request ID: %d, RPCoperation: %d, Type: %d \n", receivedMessage.getPacketID(), receivedMessage.getRpcRequestId(), receivedMessage.getRpcOperation(), receivedMessage.getMessageType());
    
    printf("received %d bytes myport <== %d ; pid %d rid %d rpco %d t %d\n",
        status, (int)ntohs(senderAddress.sin_port), pid, rid, rpco, t);
    
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
    // myaddress.sin_family = AF_INET;
    
    return myaddress;
}
