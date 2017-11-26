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

Message MySocket::callRPC(const Message & sentMessage) {

    UDPSocket rpcSocket;
    rpcSocket.bind(0);

    rpcSocket.setTimeOut(4);

    int requestsCount = 0;
    Status receiveStatus = Pending;
        
    Message receivedMessage;
    
    while(receiveStatus != Success &&
          receiveStatus != StreamFailure &&
          requestsCount++ < MAX_REQUESTS) {
        printf("try (%d) ", requestsCount);
        rpcSocket.sendPacket(sentMessage);
        
        receiveStatus = receive(rpcSocket, receivedMessage);
        
    }
    
    return receivedMessage;
}

int MySocket::recvFrom(Message & receivedMessage) {
    
    return mainSocket.recievePacket(receivedMessage);
    
}

int MySocket::reply(const Message& sentMessage) {
    
    UDPSocket replySocket;
    replySocket.bind(0);
    
    replySocket.setTimeOut(5);
    
    std::vector<Message> dividedMessage = sentMessage.divide(60);
    
    bool stopProcess = false;
    
    dividedMessage[dividedMessage.size() - 1].setMessageType(Last);
    
    for (int part = 0; part < int(dividedMessage.size()) && !stopProcess; part++) {
        
        int sentPacketCount = 0;
        
        int status = -1;
        
        while(status == -1 && sentPacketCount++ < MAX_RESEND_PACK) {
            
            replySocket.sendPacket(dividedMessage[part]);
         
            Message acknowledgementMessage;  
            status = replySocket.recievePacket(acknowledgementMessage);
            
            while(status != -1 && acknowledgementMessage.getPacketID() != part + 1) {
                
                status = replySocket.recievePacket(acknowledgementMessage);

            }
            
            printf("Server : Received acknowledgement Packet number %d\n", acknowledgementMessage.getPacketID());
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

Status MySocket::receive(UDPSocket & socket, Message & fullMessage) {
    
    Message receivedMessage;

    int status = socket.recievePacket(receivedMessage);
    
    if (status == -1) {
        return PacketFailure;
    }
    
    //int received = 1;
    
    vector<Message> messages;
    
    Message ackMessage;
    ackMessage.createMessage(0);
    ackMessage.setMessageType(Acknowledgement);
    ackMessage.setSocketAddress(receivedMessage.getSocketAddress());

    do {
        
        messages.push_back(receivedMessage);
        
        ackMessage.setPacketID(receivedMessage.getPacketID());
        
        printf("Sending Acknowledgement Packet Number : %d\n", ackMessage.getPacketID());
        
        socket.sendPacket(ackMessage);
        
        if (receivedMessage.getMessageType() == Last) {
            
            fullMessage.combine(messages);
                        
            return Success;
            
        }
        status = -1;
        
        int packetResend = 0;
        
        while(status == -1 && packetResend++ < MAX_RESEND_PACK) {
            
            do {
                status = socket.recievePacket(receivedMessage);
                
            } while(status != -1 && receivedMessage.getPacketID() != messages.size() + 1);
            
        }
        
    }while(status != -1);

    
    return StreamFailure;
    
}
