#ifndef __REQUEST_HANDLER_H
#define __REQUEST_HANDLER_H

#include <thread>
#include <map>
#include <set>
#include <deque>
#include <condition_variable>
#include <mutex>
#include <algorithm>
#include "MySocket.h"
#include "Message.h"
#include "Packet.h"


#define THREAD_COUNT 10
#define LISTENER_PORT 64000
using namespace std;
typedef  Packet (*Handler)(Packet);

deque<Packet> requestQueue;
set<int> executingRPC;
map<int, Handler> requestHandlers;

//thread threadPool[THREAD_COUNT];
MySocket requestSocket;
mutex requestQueueMtx, executingRPCMtx;
condition_variable isRequestQueueEmpty;
bool shouldShutdown = false;

void registerRequestHandler(int operationID, Handler);
void initRequestHandler();
void shutdown();
void handleRequests();
void pushToQueue(Packet msg);
void processRequest();
Packet popFromQueue();

#endif

// getImageList(string peer name)
// getImage(imgName)
// updateCount(string imgname, int newCount )
// updateCount(string imgname, )

