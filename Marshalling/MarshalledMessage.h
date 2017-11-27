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
    
protected:
    char * message;
    size_t messageSize; // WARNING unsigned
    void copyMessageArray(char *, size_t);
    
public:
    MarshalledMessage();
    MarshalledMessage(const MarshalledMessage&);
    ~MarshalledMessage();
    MarshalledMessage& operator=(const MarshalledMessage&);
    
    char * getMessageBuffer() const;
    size_t getMessageSize() const;
    
    void createMessage(size_t);
    void fillMessage(char *);
    char& operator[](int);
};

#endif /* Message_hpp */

// each class has their own marshalling logic
