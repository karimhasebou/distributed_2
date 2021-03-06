

#include "RpcStub.h"
#include "RpcCalls.h"
#include "../Marshalling/MarshallingManager.h"
#include "../Marshalling/MarshalledMessage.h"
#include "../CustomObjects/CustomObject.h"
#include "../CustomObjects/CustomString.h"
#include "../CustomObjects/CustomBool.h"
#include "../CustomObjects/CustomVector.h"
#include "../CustomObjects/CustomInt.h"

using namespace std;

//returns username of currently logged-in user
Message isOnline(Message& messageParamters)
{
    string currentlyLoggedIn = server::pingUser();
    
    if((int)currentlyLoggedIn.size() > 0){
        vector<CustomObject*> marshallingVector;
        
        CustomString *customImage = new CustomString;
        customImage->setValue(currentlyLoggedIn);
        
        marshallingVector.push_back(customImage);
        
        MarshalledMessage marshalledMsg;
        marshal(marshalledMsg, marshallingVector);
        
        Message replyMessage(marshalledMsg);
        replyMessage.setSocketAddress(messageParamters.getSocketAddress());
        replyMessage.setMessageType(Reply);
        replyMessage.setRpcRequestID(messageParamters.getRpcRequestId());
        replyMessage.setRpcOperation(messageParamters.getRpcOperation());
        
        return replyMessage;
        
    }
    
    //change
    Message mes;
    return mes;
}

Message canUpdateCount(Message& messageParamters)
{
    vector<CustomObject*> marshallingVector;
    marshallingVector.push_back(new CustomString());
    unmarshal(messageParamters, marshallingVector);
    
    string imagename = ((CustomString*) marshallingVector[0])->getValue();
    string username = ((CustomString*) marshallingVector[1])->getValue();
    
    CustomBool *wasUpdated = new CustomBool();
    wasUpdated->setValue(server::canUpdateCount(imagename, username));
    
    marshallingVector.clear();
    marshallingVector.push_back(wasUpdated);
    
    MarshalledMessage marshalledMsg;
    marshal(marshalledMsg, marshallingVector);
    
    Message replyMessage(marshalledMsg);
    replyMessage.setSocketAddress(messageParamters.getSocketAddress());
    replyMessage.setMessageType(Reply);
    replyMessage.setRpcRequestID(messageParamters.getRpcRequestId());
    replyMessage.setRpcOperation(messageParamters.getRpcOperation());
    
    return replyMessage;
}

Message updateCount(Message& messageParamters)
{
    vector<CustomObject*> marshallingVector;
    marshallingVector.push_back(new CustomString());
    marshallingVector.push_back(new CustomString());
    marshallingVector.push_back(new CustomInt());
    unmarshal(messageParamters, marshallingVector);
    
    string imagename = ((CustomString*) marshallingVector[0])->getValue();
    string username = ((CustomString*) marshallingVector[1])->getValue();
    int viewCount = ((CustomInt*) marshallingVector[2])->getValue();
    
    CustomBool *wasUpdated = new CustomBool();
    wasUpdated->setValue(server::updateCount(imagename, username, viewCount));
    
    marshallingVector.clear();
    marshallingVector.push_back(wasUpdated);
    
    MarshalledMessage marshalledMsg;
    marshal(marshalledMsg, marshallingVector);
    
    Message replyMessage(marshalledMsg);
    replyMessage.setSocketAddress(messageParamters.getSocketAddress());
    replyMessage.setMessageType(Reply);
    replyMessage.setRpcRequestID(messageParamters.getRpcRequestId());
    replyMessage.setRpcOperation(messageParamters.getRpcOperation());
    
    return replyMessage;
}

Message getImage(Message& messageParamters)
{
    vector<CustomObject*> marshallingVector;
    
    marshallingVector.push_back(new CustomString());
    
    unmarshal(messageParamters, marshallingVector);
    
    string imageName = ((CustomString*) marshallingVector[0])->getValue();
    
    marshallingVector.clear();
    
    Image imgArray = server::getImage(imageName);
    
    if(imgArray.content == NULL)
    {
        puts("failed to load image, not going to reply xp");
    }
    
    string imageString(imgArray.content, imgArray.length);
    
    delete[] imgArray.content; // free image memory
    
    CustomString *customImage = new CustomString;
    customImage->setValue(imageString);
    
    marshallingVector.push_back(customImage);
    
    MarshalledMessage marshalledMsg;
    marshal(marshalledMsg, marshallingVector);
    
    Message replyMessage(marshalledMsg);
    replyMessage.setSocketAddress(messageParamters.getSocketAddress());
    replyMessage.setMessageType(Reply);
    replyMessage.setRpcRequestID(messageParamters.getRpcRequestId());
    replyMessage.setRpcOperation(messageParamters.getRpcOperation());
    
    return replyMessage;
}

Message getAccessibleImages(Message & messageParamters)
{
    vector<CustomObject*> unmarshalledValues;
    unmarshalledValues.push_back(new CustomString());
    
    unmarshal(messageParamters, unmarshalledValues);
    
    string username = ((CustomString*) unmarshalledValues[0])->getValue();
    
    CustomVector *result = new CustomVector();

    printf("Go into the stub\n");
    
    for(string& item : server::getAccessibleImages(username)){
        result->push_back(item);
    }

    printf("finished server function\n");

    
    unmarshalledValues.clear();
    unmarshalledValues.push_back(result);
    
    MarshalledMessage marshalledMsg;
    marshal(marshalledMsg, unmarshalledValues);
    
    Message replyMessage(marshalledMsg);
    replyMessage.setSocketAddress(messageParamters.getSocketAddress());
    replyMessage.setMessageType(Reply);
    replyMessage.setRpcRequestID(messageParamters.getRpcRequestId());
    replyMessage.setRpcOperation(messageParamters.getRpcOperation());

    printf("Returning Reply::getImages>>>>\n");
    
    return replyMessage;
}
