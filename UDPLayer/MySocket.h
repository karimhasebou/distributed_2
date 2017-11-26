#ifndef __MY_SOCKET__
#define __MY_SOCKET__

#include "../UDPLayer/Message.h"
#include "UDPSocket.h"
#include <vector>
#define CHUNK_SIZE 1000   // adjust
#define MAX_RESEND 5       // adjust
#define MAX_RESEND_PACK 5  // adjust
#define MAX_REQUESTS 5     // adjust
#define MAX_RECEIVE 5      // adjust
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
    Status receive(UDPSocket&, Message&);
    Status send(UDPSocket&, const Message&);

    
public:
    MySocket();
    ~MySocket(){};
    void bind(const unsigned short&);
    
    Message callRPC(const Message&);
    int reply(const Message&);
    int recvFrom(Message&);
};

#endif 
