#include "RequestHandler.h"
#include <string>


/**
 * #include "requestHandler.h"
 * #include 
 * registerRQ(4, getimage) 
 * reisgterRQ(5, updateCount)
 * initRequestHandler();
 * 
 */

deque<Message> requestsQueue;
set<std::string> executingRPC;
map<int, Handler> requestsHandlers;

MySocket mainSocket;
mutex requestQueueMtx, executingRPCMtx;
condition_variable isRequestQueueEmpty;
bool shouldShutdown = false;

thread threadPool[THREAD_COUNT];
thread requestListener;

std::string getMessageUniqueKey(Message);

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
    isRequestQueueEmpty.notify_all();
    requestListener.join(); // wait for receivefrom to timeout
}

void handleRequests()
{
    while(!shouldShutdown){
        
        Message requestMessage;
        
        if(mainSocket.recvFrom(requestMessage) >= 0){
            printf("server got a message rpco %d ", requestMessage.getRpcOperation());
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
//    discardMessage = executingRPC.count(receivedMessage.getIPAdrress() + std::to_string(receivedMessage.getRpcOperation())) > 0;
    std::string receivedMsgKey = getMessageUniqueKey(receivedMessage);
    discardMessage = executingRPC.count(receivedMsgKey) > 0;
    printf("KEY %s\n", receivedMsgKey.c_str());
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
        std::string msgKey = getMessageUniqueKey(msg);
        std::string queueMsgKey = getMessageUniqueKey(item);
        if(msgKey == queueMsgKey){
            return true;
        }
    }
    return false;
}

Message popFromQueue()
{
    Message receivedMessage;
    std::unique_lock<std::mutex> lck(requestQueueMtx);

    while((int)requestsQueue.size() == 0 &&
        !shouldShutdown)
        isRequestQueueEmpty.wait(lck);

    if(!shouldShutdown){
        receivedMessage = requestsQueue.front();
        requestsQueue.pop_front();
    }

    return receivedMessage;
}

void processRequest()
{
    while(true){
        Message receivedMessage = popFromQueue();
        if(!shouldShutdown){
            int rpcOperation = receivedMessage.getRpcOperation();
        
        std::string msgKey = getMessageUniqueKey(receivedMessage);
        executingRPCMtx.lock();
        executingRPC.insert(msgKey);
        executingRPCMtx.unlock();

        if(requestsHandlers.count(rpcOperation) > 0){
            
            Message replyMessage = requestsHandlers[rpcOperation](receivedMessage);
            mainSocket.reply(replyMessage);
        }
        printf("request handled\n");
        executingRPCMtx.lock();
        executingRPC.erase(msgKey);
        executingRPCMtx.unlock();

        }
    }
}

std::string getMessageUniqueKey(Message message)
{
    std::string key = message.getIPAdrress() + std::to_string(message.getRpcOperation());
    return key;
}
