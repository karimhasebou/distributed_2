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


void canUpdateCount(Message)
{

}

void updateCount(Message)
{

}

void getImage(Message imgMsg)
{
	vector<CustomObject*> marshallingVector;
	marshallingVector.push_back(new CustomString());

	unmarshal(imgMsg, marshallingVector);

	string imageName = ((CustomString*)
		marshallingVector[0])->getValue();

	puts("requested Image name:" );
	puts(imageName.c_str());

	marshallingVector.clear();

	Image imgArray = getImage(imageName);

	if(imgArray.content == NULL)
	{
		puts("failed to load image, not going to reply xp");
		return;
	}
	// string imageString = "";
	// for (int i = 0; i < 1500; ++i)
	// {
	// 	imageString += (char) 0xaa;
	// }
	string imageString(imgArray.content, imgArray.length);
	delete[] imgArray.content; // free image memory

	CustomString *customImage = new CustomString;
	customImage->setValue(imageString);

	marshallingVector.push_back(customImage);

	MarshalledMessage marshalledMsg;
	marshal(marshalledMsg, marshallingVector);
	
	Message replyMessage(marshalledMsg);
    replyMessage.setSocketAddress(imgMsg.getSocketAddress());
	replyMessage.setMessageType(Reply);
    replyMessage.setRpcRequestID(imgMsg.getRpcRequestId());
    replyMessage.setRpcOperation(imgMsg.getRpcOperation());
	// replyMessage.setRpcRequestID(0xffffffff);
    // replyMessage.setRpcOperation(0xffffffff);

	MySocket socket;
    socket.bind(0);

	socket.reply(replyMessage);
}

void getAccessibleImages(Message msg)
{
	vector<CustomObject*> unmarshalledValues;
	unmarshalledValues.push_back(new CustomString());

	unmarshal(msg, unmarshalledValues);

	string username = ((CustomString*) 
		unmarshalledValues[0])->getValue();
	
	CustomVector *result = new CustomVector();
	vector<string> testResults = {"karim", "farid",};

	// RETURN THIS CODE
	// for(string& item : getAccessibleImages(username)){
	// 	result->push_back(item);
	// }

	// REMOVE AFTER TESTS HAVE BEEN DONE
	for(auto& item : testResults){
		result->push_back(item);
	}

	CustomString* string_res = new CustomString();
	string_res->setValue("karim");

	unmarshalledValues.clear();
	unmarshalledValues.push_back(result);
	//unmarshalledValues.push_back(string_res);

	MarshalledMessage marshalledMsg;
	marshal(marshalledMsg, unmarshalledValues);
	
	Message replyMessage(marshalledMsg);
    replyMessage.setSocketAddress(msg.getSocketAddress());
    replyMessage.setMessageType(Reply);
    replyMessage.setRpcRequestID(msg.getRpcRequestId());
    replyMessage.setRpcOperation(msg.getRpcOperation());

	MySocket socket;
    socket.bind(0);

	socket.reply(replyMessage);	

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