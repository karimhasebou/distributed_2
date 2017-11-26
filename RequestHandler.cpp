#include "RequestHandler.h"



/**
 * #include "requestHandler.h"
 * #include 
 * registerRQ(4, getimage) 
 * reisgterRQ(5, updateCount)
 * initRequestHandler();
 * 
 */

deque<Message> requestsQueue;
set<int> executingRPC;
map<int, Handler> requestsHandlers;

MySocket mainSocket;
mutex requestQueueMtx, executingRPCMtx;
condition_variable isRequestQueueEmpty;
bool shouldShutdown = false;

thread threadPool[THREAD_COUNT];
thread requestListener;


void initRequestHandler(const unsigned short& port)
{
    printf("SERVER ");
    mainSocket.bind(port);

    for(int i = 0; i < THREAD_COUNT; ++i){
        threadPool[i] = thread(&processRequest);
    }

    requestListener = thread(&handleRequests);
}

void addRequestHandler(int operationID, Handler RPC) {
    
    requestsHandlers[operationID] = RPC;
}

void shutdown()
{
    shouldShutdown = true;
    // requestSocket.shutdown();
}

void handleRequests()
{
    while(!shouldShutdown){
        
        Message requestMessage;
        
        if(mainSocket.recvFrom(requestMessage) >= 0){
            printf("server got a message rpco %d\n", requestMessage.getRpcOperation());
            pushToQueue(requestMessage);
        
        }
        else {
            printf("server got a bad message :(\n");
        }

    }
}

void pushToQueue(Message receivedMessage)
{
    bool discardMessage;
    
    executingRPCMtx.lock();
    discardMessage = executingRPC.count(receivedMessage.getRpcOperation()) > 0;
    executingRPCMtx.unlock();
    requestQueueMtx.lock();
    discardMessage |= queueContains(receivedMessage);       // ques here
    
    if(!discardMessage){
        requestsQueue.push_back(receivedMessage);
        isRequestQueueEmpty.notify_one();
    }
    
    requestQueueMtx.unlock();
    
}

bool queueContains(Message& msg)
{
    for(auto& item : requestsQueue){
        if(item.getRpcRequestId() == msg.getRpcRequestId()){
            return true;
        }
    }
    return false;
}

Message popFromQueue()
{
    Message receivedMessage;
    std::unique_lock<std::mutex> lck(requestQueueMtx);

    while(requestsQueue.size() == 0)
        isRequestQueueEmpty.wait(lck);

    receivedMessage = requestsQueue.front();
    requestsQueue.pop_front();

    return receivedMessage;
}

void processRequest()
{
    while(!shouldShutdown){
        
        Message receivedMessage = popFromQueue();
        int rpcOperation = receivedMessage.getRpcOperation();
        
        if(requestsHandlers.count(rpcOperation) > 0){
            Message replyMessage = requestsHandlers[rpcOperation](receivedMessage);
            mainSocket.reply(replyMessage);
        }
        
        executingRPCMtx.lock();
        executingRPC.erase(rpcOperation);
        executingRPCMtx.unlock();
    }
}

