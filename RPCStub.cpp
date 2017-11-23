#include "RPCStub.h"
#include <vector>
#include "Marshalling/MarshallingManager.h"
#include "CustomObjects/CustomInt.h"
#include "CustomObjects/CustomString.h"
#include "CustomObjects/CustomObject.h"
#include "Marshalling/MarshalledMessage.h"
#include "CustomObjects/CustomVector.h"
#include "CustomObjects/CustomBool.h"
#include "MySocket.h"

using namespace std;




void getImage(Message image)
{
	// Packet image;
	// lots of shit here
}

void getAccessibleImages(Message packet)
{
	// string username;
	// CustomString* mName;
	// MarshalledMessage mmsg;
	// vector <CustomObject*> args = {new CustomString()};
	// mmsg = (MarshalledMessage)packet.getPacketMessage();
	// unmarshal(mmsg, args);
	// mName = dynamic_cast<CustomString*>(args[0]);
	// username = mName->getValue();

	// vector<string> imageList;
	// imageList = getAccessibleImages(username);

	// CustomVector* returnVal = new CustomVector();
	// for (string& img : imageList) {
	// 	returnVal->push_back(img);
	// }
	// vector <CustomObject*> reply = {returnVal}; // to be checked
	// MarshalledMessage rmmsg;
	// marshal(rmmsg, reply);
	// Message rmsg(rmmsg);
	// rmsg.setRpcOperation(0);
	// rmsg.setRpcRequestID(0);

	// MySocket socket;
	// int port = 40000;
	// socket.bind(port);
	// packet.setPacketMessage(rmsg);
	// socket.reply(packet);
}