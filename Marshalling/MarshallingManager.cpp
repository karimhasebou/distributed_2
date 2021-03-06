//
//  MarshalingManager.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "MarshallingManager.h"
#include <iostream>

void marshal(MarshalledMessage & message,
             std::vector<CustomObject*>& parameters) {
    
    std::string bufferString = "";
    
    for (int i = 0; i < (int)parameters.size(); i++) {
        
        bufferString += parameters[i]->marshal();
    }
    
    message.createMessage(size_t(bufferString.length()));
    
    for (int i = 0; i < (int)bufferString.length(); i++) {
        message[i] = bufferString[i];
    }
    
}


void unmarshal(MarshalledMessage& message,
              std::vector<CustomObject*>& parameters) {
    
    int bufferPointer = 0;
        
    for (int i = 0; i < (int)parameters.size(); i++) {
        
        bufferPointer = parameters[i]->unmarshal(message, bufferPointer);
    }
}
