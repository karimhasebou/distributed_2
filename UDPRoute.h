#ifndef __UDP_ROUTE_
#define __UDP_ROUTE_

#include "Datagram.h"
#include <vector>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

typedef struct{
    int requestNumber;
    Datagram datagram;
} Packet;


class UDPRoute{
private:
    std::vector<Packet> receiveQueue;
    int receiveQueueStart, receiveQueueCapacity;
    int receiveQueueSize;
    int socketDesc;
    void listen();
    void addToQueue(Packet packet);

    std::mutex mutex;
    std::condition_variable condWait;
public:
    UDPRoute();
    ~UDPRoute();
    int sendto(Datagram &datagram);
    Datagram recvFrom(int requestNumber, int timeout);
    void bind(unsigned short);
    void fillAddress(struct sockaddr_in&, unsigned short);
};

#endif