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
    
    sockaddr_in shit = rpcSocket.getSocketAddress();
    
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
        
        dividedMessage[part].fillHeaders();
        partitionPacket.setPacketMessage(dividedMessage[part]);
        
        int status = 0;
        
        while(status != -1 && sentPacketCount++ < MAX_RESEND_PACK) {
            
            replySocket.sendPacket(partitionPacket);
            
            Packet acknowledgementPacket;
            
            status = replySocket.recievePacket(acknowledgementPacket);
            
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
//    printf("port %d\n", (int)ntohs(packet.getDestSocketAddress().sin_port));
    
    if (status == -1) {
        return PacketFailure;
    }
    
    vector<Message> messages;
    
    Message fullMessage;
    
    Message ackMessage;
    
    ackMessage.setMessageType(Acknowledgement);
    
    Packet ackPacket;
    ackPacket.setPacketMessage(ackMessage);
    
//    messages.push_back(receivedPacket.getMessage());
//    fullMessage.combine(messages);
//    packet.setMessage(fullMessage);
    
    do {
        
        receivedPacket.getPacketMessage().extractHeaders();
        messages.push_back(receivedPacket.getPacketMessage());
        
        socket.sendPacket(ackPacket);
        
        if (receivedPacket.getPacketMessage().getMessageType() == Last) {
            
            fullMessage.combine(messages);
            packet.setPacketMessage(fullMessage);
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
