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
        Message msg;
        if(requestSocket.recvFrom(msg) == Success){
            //msg.extractHeaders();  done in socket class
            pushToQueue(msg);
        }
    }
}

bool queueContains(Message& msg)
{
    for(auto& item : requestQueue){
        if(item.getRpcRequestId() == msg.getRpcRequestId()){
            return true;
        }
    }
    return false;
}


void pushToQueue(Message msg)
{
    bool shouldDiscard;
    
    executingRPCMtx.lock();
    shouldDiscard = executingRPC.count(
        msg.getRpcOperation()) > 0;    
    executingRPCMtx.unlock();
    
    requestQueueMtx.lock();
    shouldDiscard |= queueContains(msg);
    
    if(!shouldDiscard){
        requestQueue.push_back(msg);
        isRequestQueueEmpty.notify_one();
    }
    
    requestQueueMtx.unlock();

}

Message popFromQueue()
{
    Message msg;
    std::unique_lock<std::mutex> lck(requestQueueMtx);

    while(requestQueue.size() == 0)
        isRequestQueueEmpty.wait(lck);

    msg = requestQueue.front();
    requestQueue.pop_front();

    return msg;
}

void processRequest()
{
    while(!shouldShutdown){
        Message packet = popFromQueue();
        int rpcOperation = packet.getRpcOperation();
        
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