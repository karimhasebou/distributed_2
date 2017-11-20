//
//  main.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/15/17.
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
    
    CustomString * customString = new CustomString("w");
    
    CustomObject * bigboss = customString;
    
    std::vector<CustomObject *> parameters = {bigboss};
    
    MarshalledMessage marshalledMessage;
    
    marshal(marshalledMessage, parameters);
    
    Message sentMessage(marshalledMessage);
    
    sentMessage.setMessageType(Acknowledgement);
    sentMessage.setRpcOperation(1);
    sentMessage.setRpcOperation(2);
    
    UDPSocket socket;
    socket.bind(64000);
    
    Datagram datagram("localhost", 64000);
    datagram.setMessage(sentMessage);
    
    socket.sendDatagram(datagram);
    
    std::cout<<"Sent Packet"<<std::endl;
    
}
