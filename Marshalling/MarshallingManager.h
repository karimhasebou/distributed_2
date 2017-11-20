//
//  MarshallingManager.h
//  distributed_hw2
//
//  Created by Farida Eid on 11/17/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#ifndef MarshallingManager_h
#define MarshallingManager_h

#include "../CustomObjects/CustomObject.h"
#include "MarshalledMessage.h"
#include <vector>
#include <string>
#include <cstring>

void marshal(MarshalledMessage &,
             std::vector<CustomObject*>& parameters);


void unmarshal(MarshalledMessage&,
              std::vector<CustomObject*>& parameters);


#endif /* MarshallingManager_h */
