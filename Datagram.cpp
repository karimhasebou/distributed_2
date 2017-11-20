//
//  Datagram.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/19/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Datagram.h"

Datagram::Datagram(std::string ipAddress,
                   unsigned short portNumber) {
    
    sAddress.sin_family = AF_INET;
    sAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    sAddress.sin_port = htons(portNumber);
}

void Datagram::setMessage(Message & message) {
    
    this->message = message;
}

void Datagram::setDestIPAddress(const std::string ipAddress) {
    
    sAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
}

void Datagram::setDestPortNumber(const unsigned short &portNumber) {
    
    sAddress.sin_port = htons(portNumber);
}

Message Datagram::getMessage() {
    
    return message;
}

sockaddr_in& Datagram::getDestSocketAddress() {
    
    return sAddress;
}
