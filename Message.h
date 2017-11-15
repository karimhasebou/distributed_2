#ifndef Message_hpp
#define Message_hpp

#include <iostream>

enum MessageType {
    Request,
    Reply
};

class Message {
    
private:
    MessageType type;
    int operation;
    void * buffer;
    size_t messageSize;
    
public:
    Message();
    
    MessageType getMessageType();
    void * getMessage();
    size_t getMessageSize();
    
    void setMessageType(const MessageType& type);
    void setOperationId(int oper);
    void fillMessageBuffer(void * content, size_t size);
};

#endif /* Message_hpp */

// each class has their own marshalling logic
