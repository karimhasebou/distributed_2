#ifndef __RPCStub
#define __RPCStub
#include "RPC.h"
#include "Packet.h"

void getImage(Packet);
void getAccessibleImages(Packet);
void canUpdateCount(Packet);
void updateCount(Packet);

#endif