#include "RequestHandler.h"
#include "MySocket.h"
#include "Message.h"
#include "RPCStub.h"
#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    using namespace std::chrono;
    
    puts("SERVER CONSOLE\n");
    
    
    MySocket mySocket;
    mySocket.bind(63000);
    
    Message replyMessage;
    mySocket.recvFrom(replyMessage);
    
    
    return 0;
}
