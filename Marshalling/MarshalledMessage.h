//
//  MarshallingMessage.h
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef MarshalledMessage_hpp
#define MarshalledMessage_hpp

#include <iostream>

class MarshalledMessage {
    
private:
    char * message;
    size_t messageSize;
    int startPosition;
    
public:
    MarshalledMessage();
    ~MarshalledMessage();
    
    char * getMessage();
    size_t getMessageSize();
    
    void createMessage(size_t);
    char& operator[](int);
    void updateStartPosition(int);
};

#endif /* Message_hpp */

// each class has their own marshalling logic
