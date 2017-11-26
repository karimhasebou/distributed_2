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
    registerRequestHandler(1, getAccessibleImages);
    registerRequestHandler(2, getImage);
    
    initRequestHandler();
    
    std::this_thread::sleep_for(std::chrono::seconds(60));
    puts("server shutting down...\n");
    
    shutdown();
    
    std::this_thread::sleep_for(std::chrono::seconds(60));
    puts("server shut down...\n");

    return 0;
}
