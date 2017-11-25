#ifndef __RPCStub
#define __RPCStub
#include "RPC.h"
#include "../UDPLayer/Message.h"

Message isOnline(Message&);     //returns username of currently logged-in user
Message getImage(Message&);
Message getAccessibleImages(Message&);
Message canUpdateCount(Message&);
Message updateCount(Message&);

Message login(Message&);
Message getIPAddress(Message&);
Message getUsername(Message&);
#endif
