//
//  Packet.cpp
//  distributed_hw2
//
//  Created by Farida Eid on 11/19/17.
//  Copyright © 2017 Farida Eid. All rights reserved.
//

#include "Packet.h"

Packet::Packet(std::string ipAddress,
                   unsigned short portNumber) {
    
    sAddress.sin_family = AF_INET;
    sAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    sAddress.sin_port = htons(portNumber);
}

void Packet::setPacketMessage(Message & message) {
    
    this->message = message;
}

void Packet::setDestIPAddress(const std::string ipAddress) {
    
    sAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
}

void Packet::setSocketAddress(const sockaddr_in & sockAddress) {
    
    sAddress = sockAddress;
}

void Packet::setDestPortNumber(const unsigned short &portNumber) {
    
    sAddress.sin_port = htons(portNumber);
}

Message& Packet::getPacketMessage() {
    return message;
}

const Message& Packet::getPacketMessage() const {
    return message;
}

sockaddr_in Packet::getSocketAddress() const {
    
    return sAddress;
}
