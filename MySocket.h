#ifndef __MY_SOCKET__
#define __MY_SOCKET__

#include "Message.h"
#include "UDPSocket.h"
#include "Packet.h"
#include <vector>
#define CHUNK_SIZE 312231   // adjust
#define MAX_RESEND 40       // adjust
#define MAX_RESEND_PACK 10  // adjust
#define MAX_REQUESTS 10     // adjust
#define MAX_RECEIVE 12      // adjust
#define TIMEOUT 11          // adjust

enum Status {
    PacketFailure,
    StreamFailure,
    Pending,
    Success
};

class MySocket{
    
private:
    UDPSocket mainSocket;
    Status receive(UDPSocket&, Packet&);
    Status send(UDPSocket&, const Packet&);

    
public:
    MySocket();
    ~MySocket(){};
    void bind(const unsigned short&);
    
    Message callRPC(const Packet&);
    int reply(const Packet&);
    int recvFrom(Packet&);
};

#endif 