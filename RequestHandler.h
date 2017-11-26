#ifndef __REQUEST_HANDLER_H
#define __REQUEST_HANDLER_H

#include <thread>
#include <map>
#include <set>
#include <deque>
#include <condition_variable>
#include <mutex>
#include <algorithm>
#include "UDPLayer/MySocket.h"
#include "UDPLayer/Message.h"

#define THREAD_COUNT 10

using namespace std;

typedef  Message (*Handler)(Message&);

void initRequestHandler(const unsigned short&);
void addRequestHandler(int operationID, Handler);
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

