//
//  main2.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/19/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Marshalling/MarshallingManager.h"
#include "CustomObjects/CustomInt.h"
#include "CustomObjects/CustomString.h"
#include "CustomObjects/CustomObject.h"
#include "Marshalling/MarshalledMessage.h"
#include "CustomObjects/CustomVector.h"
#include "CustomObjects/CustomBool.h"
#include "Message.h"
#include "UDPSocket.h"
#include "Datagram.h"
#include <iostream>

int main() {
    
    UDPSocket socket;
    socket.bind(64000);
    
    Message recievedMessage;
    
    int status = socket.recieveDatagram(recievedMessage);
    
    MarshalledMessage marshalledMessage = recievedMessage;
    
    std::vector<CustomObject* > returnValues = {new CustomString()};
    
    unmarshal(marshalledMessage, returnValues);
    
    CustomString * returnValueString = dynamic_cast<CustomString *>(returnValues[0]);

    std::cout<<returnValueString->getValue()<<std::endl;
    
    
    
}
