//
//  CustomInt.hpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/15/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef CustomInt_hpp
#define CustomInt_hpp

#include "CustomObject.h"

class CustomInt : public CustomObject {
    
private:
    int value;
    
public:
    CustomInt(){}
    CustomInt(const int&);
    void setValue(const int&);
    int getValue();
    virtual std::string marshal();
    virtual int unmarshal(char *, const int&);
    
};

#endif /* CustomInt_hpp */
