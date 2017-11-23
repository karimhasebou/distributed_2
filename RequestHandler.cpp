#include "RequestHandler.h"

/**
 * #include "requestHandler.h"
 * #include 
 * registerRQ(4, getimage)
 * reisgterRQ(5, updateCount)
 * initRequestHandler();
 * 
 */


void initRequestHandler()
{
    requestSocket.bind(LISTENER_PORT);

    for(int i = 0; i < THREAD_COUNT; ++i){
        thread threadPool(processRequest);
    }

    thread requestListener(handleRequests);
}

void shutdown()
{
    shutdown = true;
    requestSocket.shutdown();
}

void handleRequests()
{
    Packet packet;
    while(!shutdown){
        if(requestSocket->recvFrom(packet) == Success){
            pushToQueue(packet.message);
        }
    }
}

void pushToQueue(Message msg)
{processingQueue
processingQueue
processingQueue
    bool shouldDiscard;
    
    executingRPCMtx.lock();
    shouldDiscard = executingRPC.count(msg.rpcRequestID) > 0;    
    executingRPCMtx.unlock();
    
    requestQueueMtx.lock();
    shouldDiscard |= std::find(requestQueue.begin(), 
        requestQueue.end(), msg) != requestQueue.end();
    
    if(!shouldDiscard){
        requestQueue.push_back(msg);
        isRequestQueueEmpty.notify_one();
    }
    
    requestQueueMtx.unlock();

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
        int rpcOperation = msg.getRpcOperation();
        
        if(map.count(rpcOperation) > 0){
            map[rpcOperation](msg);
        }

        executingRPCMtx.lock();
        executingRPC.erase(msg);
        executingRPCMtx.unlock();
    }
}

void registerRequestHandler(int operationID, 
    Message (*handler)(Message))
{
    requestHandlers[operationID] = handler;
}