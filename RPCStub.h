#ifndef __RPCStub
#define __RPCStub
#include "RPC.h"
#include "Message.h"

void getImage(Message);
void getAccessibleImages(Message);
void canUpdateCount(Message);
void updateCount(Message);


#endif