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
    
    std::vector<CustomObject* > returnValues = {new CustomString(), new CustomInt(), new CustomVector(), new CustomBool()};
    
    unmarshal(marshalledMessage, returnValues);
    
    CustomString * returnValueString = dynamic_cast<CustomString *>(returnValues[0]);
    
    CustomInt * returnValueInt = dynamic_cast<CustomInt *>(returnValues[1]);
    
    CustomVector * returnValueVector = dynamic_cast<CustomVector *>(returnValues[2]);
    
    CustomBool * returnValueBool = dynamic_cast<CustomBool *>(returnValues[3]);

    std::cout<<returnValueString->getValue()<<std::endl;
    
    std::cout<<returnValueInt->getValue()<<std::endl;
    
    for(int i = 0; i < returnValueVector->getValue().size(); i++) {
        
        std::cout<<returnValueVector->getValue()[i]<<std::endl;
        
    }
    
    if (returnValueBool->getValue()) {
        std::cout<<"Value is true"<<std::endl;
    } else {
        std::cout<<"Value is false"<<std::endl;
    }
    
    
    
}
