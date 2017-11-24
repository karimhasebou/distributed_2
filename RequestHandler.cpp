#include "RequestHandler.h"


deque<Message> requestQueue;
set<int> executingRPC;
map<int, Handler> requestHandlers;

//thread threadPool[THREAD_COUNT];
MySocket requestSocket;
mutex requestQueueMtx, executingRPCMtx;
condition_variable isRequestQueueEmpty;
bool shouldShutdown = false;

thread threadPool[THREAD_COUNT];
thread requestListener;

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
        threadPool[i] = thread(processRequest);
    }

    requestListener = thread(handleRequests);
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
        puts("waiting for incoming requests zzz");
        if(requestSocket.recvFrom(msg) >= 0){
            puts("received msg");
            //msg.extractHeaders();  done in socket class
            pushToQueue(msg);
            puts("pushed to queue");
        }
        else {
            puts("received request is bad :'(");
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