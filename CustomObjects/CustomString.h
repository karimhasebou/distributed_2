//
//  CustomString.hpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/15/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef CustomString_hpp
#define CustomString_hpp

#include "CustomObject.h"
#include <string>

class CustomString : public CustomObject {
private:
    std::string value;
    
public:
    CustomString(){}
    CustomString(const std::string&);
    void setValue(const std::string&);
    std::string getValue();
    virtual std::string marshal();
    virtual int unmarshal(MarshalledMessage &, const int&);
};

#endif /* CustomString_hpp */
