//
//  CustomVector.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/16/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "CustomVector.h"
#include "CustomInt.h"
#include "CustomString.h"


void CustomVector::push_back(const std::string & str) {
    this->value.push_back(str);
}

std::vector<std::string> CustomVector::getValue() {
    return value;
}

std::string& CustomVector::operator[](int index) {
    if (index < 0 || index >= value.size()) {
        throw ("Bad access");
    }
    
    return value[index];
}

std::string CustomVector::marshal() {
    
    CustomInt vectorLength((int)this->value.size());
    
    std::string marshalledVector = vectorLength.marshal();
    
    CustomString stringElement;
    
    for (std::string element : value) {
        
        stringElement.setValue(element);
        
        marshalledVector += stringElement.marshal();
    }

    return marshalledVector;
}

int CustomVector::unmarshal(MarshalledMessage & buffer, const int & startPosition) {
    
    int bufferPosition = startPosition;
    
    CustomInt vectorLength;
    
    CustomString stringElement;
    
    this->value.resize(0);
    
    bufferPosition = vectorLength.unmarshal(buffer, startPosition);
    
    for (int i = 0; i < vectorLength.getValue(); i++) {
        
        bufferPosition = stringElement.unmarshal( buffer, bufferPosition);
        
        value.push_back(stringElement.getValue());
        
    }
    
    return bufferPosition;
}

