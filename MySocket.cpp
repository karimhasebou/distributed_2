#include "MySocket.h"
#define SUCCESS 1
#define FAIL 0
using namespace std;

MySocket::MySocket()
{
    // get the available ports
}

void MySocket::bind(const unsigned short & portNumber) {
    
    mainSocket.bind(portNumber);
    
}

Message MySocket::callRPC(const Packet & sentPacket) {

    UDPSocket rpcSocket;
    rpcSocket.bind(0);
    
    sockaddr_in address = rpcSocket.getSocketAddress();
    int sockDesc = rpcSocket.getSockDesc();
    socklen_t address_length = sizeof address;
    
    getsockname(sockDesc,(sockaddr *)&address, &address_length);
    
    rpcSocket.bind((int)ntohs(address.sin_port));

    int requestsCount = 0;
    Status receiveStatus = Pending;
        
    Packet receivedPacket;
    
    while(receiveStatus != Success &&
          receiveStatus != StreamFailure &&
          requestsCount++ < MAX_REQUESTS) {
        
        rpcSocket.sendPacket(sentPacket);
        
        receiveStatus = receive(rpcSocket, receivedPacket);
        
    }
    
    return receivedPacket.getPacketMessage();
}

int MySocket::recvFrom(Packet & receivedPacket) {
    
    return mainSocket.recievePacket(receivedPacket);
    
}

int MySocket::reply(const Packet& sentPacket) {
    
    UDPSocket replySocket;
    replySocket.bind(0);
    
    std::vector<Message> dividedMessage = sentPacket.getPacketMessage().divide(CHUNK_SIZE);
    
    Packet partitionPacket = sentPacket;
    bool stopProcess = false;
    
    dividedMessage[dividedMessage.size() - 1].setMessageType(Last);
    
    for (int part = 0; part < dividedMessage.size() && !stopProcess; part++) {
        
        int sentPacketCount = 0;
        
        partitionPacket.setPacketMessage(dividedMessage[part]);
        
        int status = 0;
        
        while(status != -1 && sentPacketCount++ < MAX_RESEND_PACK) {
            
            replySocket.sendPacket(partitionPacket);
            
            Packet acknowledgementPacket;
            
            status = replySocket.recievePacket(acknowledgementPacket);
            
            printf("Received acknowledgement Packet\n\n");
            // doing the checks
        }
        
        if (status == -1) {
            stopProcess = true;
        }
        
    }
        
    if (stopProcess) {
        
        return FAIL;
        
    }
    
    return SUCCESS;
    
}

Status MySocket::receive(UDPSocket & socket, Packet & packet) {
    
    Packet receivedPacket;
    int status = socket.recievePacket(receivedPacket);
    
    if (status == -1) {
        return PacketFailure;
    }
    
    vector<Message> messages;
    
    Message ackMessage;
    ackMessage.setMessageType(Acknowledgement);
    
    Packet ackPacket;
    ackPacket.setPacketMessage(ackMessage);
    
    do {
        
        messages.push_back(receivedPacket.getPacketMessage());
        
        printf("Sending Acknowledgement packet\n\n");
        
        socket.sendPacket(ackPacket);
        
        if (receivedPacket.getPacketMessage().getMessageType() == Last) {
            
            packet.getPacketMessage().combine(messages);
                        
            return Success;
            
        }
        
        status = -1;
        
        int packetResend = 0;
        
        while(status == -1 && packetResend++ < MAX_RESEND_PACK) {
            
            status = socket.recievePacket(receivedPacket);
            
        }
        
    } while(status != -1);
    
    
    return StreamFailure;
    
}
