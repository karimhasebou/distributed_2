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
    shouldShutdown = true;
    // requestSocket.shutdown();
}

void handleRequests()
{
    while(!shouldShutdown){
        Packet packet;
        if(requestSocket.recvFrom(packet) == Success){
            packet.getPacketMessage().extractHeaders();
            pushToQueue(packet);
        }
    }
}

void pushToQueue(Packet packet)
{
    bool shouldDiscard;
    
    executingRPCMtx.lock();
    shouldDiscard = executingRPC.count(packet.getPacketMessage().getRpcOperation()) > 0;    
    executingRPCMtx.unlock();
    
    requestQueueMtx.lock();
    shouldDiscard |= std::find(requestQueue.begin(), 
        requestQueue.end(), packet) != requestQueue.end();
    
    if(!shouldDiscard){
        requestQueue.push_back(packet);
        isRequestQueueEmpty.notify_one();
    }
    
    requestQueueMtx.unlock();

}

Packet popFromQueue()
{
    Packet packet;
    std::unique_lock<std::mutex> lck(requestQueueMtx);

    while(requestQueue.size() == 0)
        isRequestQueueEmpty.wait(lck);

    packet = requestQueue.front();
    requestQueue.pop_front();

    return packet;
}

void processRequest()
{
    while(!shouldShutdown){
        Packet packet = popFromQueue();
        int rpcOperation = packet.getPacketMessage().getRpcOperation();
        
        if(requestHandlers.count(rpcOperation) > 0){
            requestHandlers[rpcOperation](packet);
        }

        executingRPCMtx.lock();
        executingRPC.erase(rpcOperation);
        executingRPCMtx.unlock();
    }
}

void registerRequestHandler(int operationID, 
    Handler RPC)
{
    requestHandlers[operationID] = RPC;
}