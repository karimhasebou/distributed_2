//
//  CustomBool.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/16/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "CustomBool.h"

CustomBool::CustomBool(const bool& value) {
    this->value = value;
}

void CustomBool::setValue(const bool & value) {
    this->value = value;
}

bool CustomBool::getValue() {
    return this->value;
}

std::string CustomBool::marshal() {
    
    std::string bytes = "";
    
    bytes += (char)value;
    
    return bytes;
    
}

int CustomBool::unmarshal(char * buffer, const int & bufferIndex) {
    
    value = (bool)buffer[bufferIndex];
    
    return bufferIndex + 1;
    
}
