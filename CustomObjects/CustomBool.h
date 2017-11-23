//
//  CustomBool.hpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/16/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef CustomBool_hpp
#define CustomBool_hpp

#include "CustomObject.h"

class CustomBool : public CustomObject {
    
private:
    bool value;
    
public:
    CustomBool(){}
    CustomBool(const bool&);
    void setValue(const bool&);
    bool getValue();
    virtual std::string marshal();
    virtual int unmarshal(MarshalledMessage &, const int&);
    
};


#endif /* CustomBool_hpp */
