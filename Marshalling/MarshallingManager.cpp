//
//  MarshalingManager.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "MarshallingManager.h"
#include <iostream>

MarshalledMessage marshal(std::vector<CustomObject*>& parameters) {
    
    std::string bufferString = "";
    
    for (int i = 0; i < parameters.size(); i++) {
        
        bufferString += parameters[i]->marshal();
    }
    
    MarshalledMessage message;
    message.createMessage(size_t(bufferString.length()));
    
    for (int i = 0; i < bufferString.length(); i++) {
        message[i] = bufferString[i];
    }
    
    return message;
    
}


int unmarshal(MarshalledMessage& message,
              const int& startPointer,
              std::vector<CustomObject*>& parameters) {
    
    int bufferPointer = startPointer;
    
    char * buffer = message.getMessage();
    
    for (int i = 0; i < parameters.size(); i++) {
        
        bufferPointer = parameters[i]->unmarshal(buffer, bufferPointer);
    }
    
    return bufferPointer;
}
