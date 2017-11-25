#ifndef __RPCStub
#define __RPCStub
#include "RPC.h"
#include "Message.h"

void getImage(Message);
void getAccessibleImages(Message);
void canUpdateCount(Message);
void updateCount(Message);

void isOnline(Message);     //returns username of currently logged-in user
void serverLogin(Message);   // checks server db for given credentials



#endif