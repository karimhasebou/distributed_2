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

//returns username of currently logged-in user
void isOnline(Message request)
{
	string currentlyLoggedIn = getLoggedUsername();

	if(currentlyLoggedIn.size() > 0){
		vector<CustomObject*> marshallingVector;

		CustomString *customImage = new CustomString;
		customImage->setValue(currentlyLoggedIn);

		marshallingVector.push_back(customImage);

		MarshalledMessage marshalledMsg;
		marshal(marshalledMsg, marshallingVector);
		
		Message replyMessage(marshalledMsg);
		replyMessage.setSocketAddress(request.getSocketAddress());
		replyMessage.setMessageType(Reply);
		replyMessage.setRpcRequestID(request.getRpcRequestId());
		replyMessage.setRpcOperation(request.getRpcOperation());

		MySocket socket;
		socket.bind(0);

		socket.reply(replyMessage);
	}
}

// checks server db for given credentials
// incomplete
void serverLogin(Message request)
{
	vector<CustomObject*> marshallingVector;
	marshallingVector.push_back(new CustomString());
	unmarshal(request, marshallingVector);

	string username = ((CustomString*) marshallingVector[0])->getValue();
	string password = ((CustomString*) marshallingVector[1])->getValue();


}

void canUpdateCount(Message request)
{
	vector<CustomObject*> marshallingVector;
	marshallingVector.push_back(new CustomString());
	unmarshal(request, marshallingVector);

	string imagename = ((CustomString*) marshallingVector[0])->getValue();
	string username = ((CustomString*) marshallingVector[1])->getValue();

	CustomBool *wasUpdated = new CustomBool();
	wasUpdated->setValue(canUpdateCount(imagename, username));

	marshallingVector.clear();
	marshallingVector.push_back(wasUpdated);

	MarshalledMessage marshalledMsg;
	marshal(marshalledMsg, marshallingVector);
	
	Message replyMessage(marshalledMsg);
    replyMessage.setSocketAddress(request.getSocketAddress());
	replyMessage.setMessageType(Reply);
    replyMessage.setRpcRequestID(request.getRpcRequestId());
    replyMessage.setRpcOperation(request.getRpcOperation());

	MySocket socket;
    socket.bind(0);

	socket.reply(replyMessage);
}

void updateCount(Message request)
{
	vector<CustomObject*> marshallingVector;
	marshallingVector.push_back(new CustomString());
	unmarshal(request, marshallingVector);

	string imagename = ((CustomString*) marshallingVector[0])->getValue();
	string username = ((CustomString*) marshallingVector[1])->getValue();
	int viewCount = ((CustomInt*) marshallingVector[2])->getValue();

	CustomBool *wasUpdated = new CustomBool();
	wasUpdated->setValue(updateCount(imagename, username, viewCount));

	marshallingVector.clear();
	marshallingVector.push_back(wasUpdated);

	MarshalledMessage marshalledMsg;
	marshal(marshalledMsg, marshallingVector);
	
	Message replyMessage(marshalledMsg);
    replyMessage.setSocketAddress(request.getSocketAddress());
	replyMessage.setMessageType(Reply);
    replyMessage.setRpcRequestID(request.getRpcRequestId());
    replyMessage.setRpcOperation(request.getRpcOperation());

	MySocket socket;
    socket.bind(0);

	socket.reply(replyMessage);
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
}