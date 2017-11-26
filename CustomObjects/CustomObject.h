//
//  CustomObject.h
//  distributed_hw2
//
//  Created by Farida Eid on 11/15/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef CustomObject_h
#define CustomObject_h

#include <string>
#include "../Marshalling/MarshalledMessage.h"

class CustomObject {
    
public:
    
    virtual std::string marshal() = 0;
    virtual int unmarshal(MarshalledMessage&, const int&) = 0;
    
};


#endif /* CustomObject_h */
