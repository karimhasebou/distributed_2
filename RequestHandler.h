#ifndef __REQUEST_HANDLER_H
#define __REQUEST_HANDLER_H

#include <thread>
#include <map>
#include <set>
#include <queue>
#include <<condition_variable>
#include <mutex>
#include "MySocket.h"
#include "Message.h"


#define THREAD_COUNT 10
#define LISTENER_PORT 64000
using namespace std;

queue<Message> requestQueue;
set<int> executingRPC;
map<int, Message (*handler)(Message)> requestHandlers;

//thread threadPool[THREAD_COUNT];
MySocket requestSocket;
mutex requestQueueMtx, executingRPCMtx;
condition_variable isRequestQueueEmpty;
bool shutdown = false;

void registerRequestHandler(int operationID, Message (*handler)(Message));
void initRequestHandler();
void shutdown();
void handleRequests();
void pushToQueue(Message msg);
void processRequest();
Message popFromQueue();

#endif

// getImageList(string peer name)
// getImage(imgName)
// updateCount(string imgname, int newCount )
// updateCount(string imgname, )

