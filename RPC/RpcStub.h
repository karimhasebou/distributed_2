#ifndef __RPCStub
#define __RPCStub
#include "../UDPLayer/Message.h"

Message isOnline(Message&);     //returns username of currently logged-in user
Message getImage(Message&);
Message getAccessibleImages(Message&);
Message canUpdateCount(Message&);
Message updateCount(Message&);

Message login(Message&);
Message getUsersIPAddress(Message&);
Message getUsername(Message&);
Message getUserNamefromIP(Message&);

#endif
