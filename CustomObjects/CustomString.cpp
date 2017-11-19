//
//  CustomString.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/15/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "CustomString.h"
#include "CustomInt.h"
#include <cstdio>

CustomString::CustomString(const std::string& value) {
    this->value = value;
}

void CustomString::setValue(const std::string & value) {
    this->value = value;
}

std::string CustomString::getValue() {
    return value;
}

std::string CustomString::marshal() {
    
    std::string marshalledString;
    
    CustomInt stringLength((int)value.length());
    
    marshalledString = stringLength.marshal();
    
    marshalledString += value;
    
    return marshalledString;
}

int CustomString::unmarshal(char * buffer, const int& bufferIndex) {
    
    CustomInt stringLength;
    
    int currentIndex = bufferIndex;
    
    currentIndex = stringLength.unmarshal(buffer, currentIndex);

    value = "";
    
    for (int i = 0; i < stringLength.getValue(); i++) {
        value += buffer[currentIndex + i];
    }
    
    return currentIndex + stringLength.getValue();
}

