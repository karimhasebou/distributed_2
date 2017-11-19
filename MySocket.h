#ifndef __MY_SOCKET__
#define __MY_SOCKET__

#include "Message.h"
#include "UDPSocket.h"
#include <string>
#include <vector>
#define CHUNK_SIZE 312231 // adjust
#define MAX_RESEND 40 // adjust
#define MAX_RECEIVE 12 // adjust
#define TIMEOUT 11 // adjust
// #define SUCCESS
// #define FAIL
// #define MESSAGE TYPES ... LAST

class MySocket{

public:
    int send(Message);
    int receive(Message&);

private:
    MySocket(int, std::string);
    UDPSocket socket;
    ~MySocket();
    int portNumber;
    int count_send;
    int count_receive;

    void resetRCount();
    void resetVCount();
    void sendAck(UDPSocket);

};

#endif 
