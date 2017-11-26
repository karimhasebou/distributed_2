#ifndef __MY_SOCKET__
#define __MY_SOCKET__

#include "../UDPLayer/Message.h"
#include "UDPSocket.h"
#include <vector>
#define CHUNK_SIZE 60   // adjust
#define MAX_RESEND 40       // adjust
#define MAX_RESEND_PACK 10  // adjust
#define MAC_PACK_FAIL 20    // adjust
#define MAX_REQUESTS 10     // adjust
#define MAX_RECEIVE 12      // adjust
#define TIMEOUT 11          // adjust

enum Status {
    Failure = -1,
    Pending = 0,
    Success = 1
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
    Status reply(const Message&);
    int recvFrom(Message&);
};

#endif 
