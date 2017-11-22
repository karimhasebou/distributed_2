#include "RequestHandler.h"


void initRequestHandler()
{

    thread requestListener(handleRequests);
}

void shutdown()
{
    shutdown = true;
}

void handleRequests()
{
    Packet packet;
    while(1){
        if(requestSocket->recvFrom(packet) == Success){
            pushToQueue(packet.message);
        }
    }
}


void pushToQueue(Message msg)
{
    bool shouldDiscard;
    
    processingQueueMtx.lock();
    shouldDiscard = processingQueue.count(msg.rpcRequestID) > 0;
    processingQueueMtx.unlock();
    
    if(!shouldDiscard){
        requestQueueMtx.lock();
        requestQueue.push_back(msg);
        isRequestQueueEmpty.notify_one();
        requestQueueMtx.unlock();
    }
}

Message popFromQueue()
{
    Messages msg;
    requestQueueMtx.lock();

    while(requestQueue.size() == 0)
        isRequestQueueEmpty.wait(requestQueueMtx);

    msg = requestQueue.pop();
    requestQueueMtx.unlock();

    return msg;
}

void processRequest()
{
    while(!shutdown){
        Message msg = popFromQueue();
        int rpcOperationID = msg.getRpcOperation();
        
        if(map.count(rpcOperationID) > 0){
            map[rpcOperationID](msg);
        }
    }
}

void registerRequestHandler(int operationID, 
    Message (*handler)(Message))
{
    requestHandlers[operationID] = handler;
}