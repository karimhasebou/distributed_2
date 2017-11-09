#include "UDPRoute.h"

#include <thread>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h> 
#include <chrono>

using namespace std::chrono;

UDPRoute::UDPRoute()
{
    this->socketDesc = socket(AF_INET, SOCK_DGRAM, 0);

    std::thread listenThread(listen);
}

UDPRoute::~UDPRoute()
{

}

void UDPRoute::listen()
{
    while(1)
    {
        Packet packet;
        sockaddr_in socketAddress;
        socklen_t clientLen = sizeof(socketAddress);

        int status = (int)recvfrom(this->socketDesc, 
            packet.datagram.message, packet.datagram.length, 
            MSG_WAITALL, (sockaddr *) &packet.datagram.sAddress,
                &clientLen);

        if(status != -1)
        {
            addToQueue(packet);
        }
    }
}

void UDPRoute::fillAddress(struct sockaddr_in& socket, unsigned short port)
{
    socket.sin_family = AF_INET;
    socket.sin_port = htons(port);
    socket.sin_addr.s_addr = htonl(INADDR_ANY);
}

void UDPRoute::bind(unsigned short portNumber)
{
    sockaddr_in address;
    fillAddress(address, portNumber);
    ::bind(socketDesc, (struct sockaddr*)&address, sizeof address);
}

int UDPRoute::sendto(Datagram &datagram)
{

}

Datagram UDPRoute::recvFrom(int requestNumber, int timeout)
{
    const std::chrono::milliseconds timeoutPeriod( timeout );
    bool exit = false;
    Datagram data;

    mutex.lock();
    while(!exit){
        

        for(int i = 0; i < receiveQueue.size(); ++i){
            if(receiveQueue[i].requestNumber == requestNumber){
                data = receiveQueue[i].datagram;
                receiveQueue.erase(receiveQueue.begin() + i);
                exit = true;
                break;
            }
        }
        
       // condWait.wait_for(mutex, timeoutPeriod);
    }
    mutex.unlock();
    return data;
}

void UDPRoute::addToQueue(Packet packet)
{
    receiveQueue.push_back(packet);
    // we have filled our queue time  to 
    // remove an element
    if(receiveQueue.size() >= 10){
        receiveQueue.erase(receiveQueue.begin());
    }
}