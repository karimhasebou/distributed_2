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
using namespace std;

queue<Message> requestQueue;
set<int> processingQueue;
map<int, Message (*handler)(Message)> requestHandlers;

thread threadPool[THREAD_COUNT];
MySocket *requestSocket;
mutex requestQueueMtx, processingQueueMtx;
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
