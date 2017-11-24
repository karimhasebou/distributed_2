#include "RequestHandler.h"
#include "MySocket.h"
#include "Message.h"
#include "RPCStub.h"
#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    using namespace std::chrono_literals;
    puts("SERVER CONSOLE\n");
    registerRequestHandler(1, getAccessibleImages);
    registerRequestHandler(2, getImage);
    
    initRequestHandler();

    std::this_thread::sleep_for(60s);
    puts("server shutting down...\n");

    shutdown();

    std::this_thread::sleep_for(60s);
    puts("server shut down...\n");


    return 0;
}