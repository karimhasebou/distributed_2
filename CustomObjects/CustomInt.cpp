//
//  CustomInt.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/15/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "CustomInt.h"
#include <iostream>

CustomInt::CustomInt(const int& value) {
    this->value = value;
}


void CustomInt::setValue(const int & value) {
    this->value = value;
}

int CustomInt::getValue() {
    return value;
}


std::string CustomInt::marshal() {
    
    std::string bytes = "";
    
    for (int i = 0; i < 4; i++) {
       bytes += char((value >> i*8) & 0xFF);
    }
    
    return bytes;
}

int CustomInt::unmarshal(char * buffer, const int& bufferIndex) {
    
    value = 0;
    int temp;

    for (int i = 0; i < 4; i++) {
        temp = buffer[bufferIndex + i];
        temp &= 0xff;
        value = value | (temp<<i*8);
    }
    
    
    return bufferIndex + 4;
}


