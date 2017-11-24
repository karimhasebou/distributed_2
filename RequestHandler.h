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


#define THREAD_COUNT 10
#define LISTENER_PORT 63000
using namespace std;
typedef  void (*Handler)(Message);

void registerRequestHandler(int operationID, Handler);
void initRequestHandler();
void shutdown();
void handleRequests();
void pushToQueue(Message msg);
void processRequest();
Message popFromQueue();
bool queueContains(Message& msg);

#endif

// getImageList(string peer name)
// getImage(imgName)
// updateCount(string imgname, int newCount )
// updateCount(string imgname, )

