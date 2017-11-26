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

Status MySocket::reply(const Message& sentMessage) {
    
    UDPSocket replySocket;
    replySocket.bind(0);
    
    int expectingAck = 1;
    
    replySocket.setTimeOut(5);
    
    std::vector<Message> dividedMessage = sentMessage.divide(CHUNK_SIZE);
    
    bool stopProcess = false;
    
    dividedMessage[dividedMessage.size() - 1].setMessageType(Last);
    
    for (int part = 0; part < int(dividedMessage.size()) && !stopProcess; part++) {
        
        int resendPacketCount = 1;
        
        Status status = Failure;
        
        printf("Send Packet with Packet number %d\n", dividedMessage[part].getPacketID());
        
        replySocket.sendPacket(dividedMessage[part]);

        while(status == Failure && resendPacketCount++ <= MAX_RESEND_PACK) {
            
            Message acknowledgementMessage;
            
            status = (Status)replySocket.recievePacket(acknowledgementMessage);
            
            if (status == Failure && acknowledgementMessage.getPacketID() != expectingAck) {
                
                status = (Status)replySocket.sendPacket(dividedMessage[part]);

            }
        }
        
        
        if (resendPacketCount > MAX_RESEND_PACK) {
            
            stopProcess = true;
        }
        
    }
    
    if (stopProcess) {
        
        return Failure;
    }
    
    return Success;
}

Status MySocket::receive(UDPSocket & socket, Message & fullMessage) {
    
    int expectingPacketID = 1;
    int lastAcknowledgement = 0;
    
    socket.setTimeOut(5);
    
    vector<Message> messages;
    Message receivedMessage, ackMessage;
    
    ackMessage.createMessage(0);
    ackMessage.setMessageType(Acknowledgement);
    ackMessage.setSocketAddress(receivedMessage.getSocketAddress());
    
    int packetFailure = 1;
    
    while(packetFailure <= MAX_RESEND_PACK) {
        
        Message receivedMessage;
        Status packetStatus = Pending;
        int receiveCount = 1;
        

        while (receiveCount++ <= MAX_RESEND_PACK) {
            
            packetStatus = (Status)socket.recievePacket(receivedMessage);
            
            if (packetStatus != Failure && receivedMessage.getPacketID() >= lastAcknowledgement) {
                
                printf("Recevived Message Packet Number : %d\n", receivedMessage.getPacketID());

                
                if (receivedMessage.getPacketID() == expectingPacketID) {
                    
                    messages.push_back(receivedMessage);
                    expectingPacketID++;
                    lastAcknowledgement++;
                    
                }
                
                ackMessage.setPacketID(lastAcknowledgement);
                
                printf("Sending Acknowledgement Packet Number : %d\n", ackMessage.getPacketID());

                socket.sendPacket(ackMessage);
                
                if (receivedMessage.getMessageType() == Last) {
                    
                    printf("Last Message received from server\n");
                    
                    fullMessage.combine(messages);
                    
                    return Success;
                }
            }
            
            if (packetStatus == Failure) {
                
                packetFailure++;
            }
        }
    }
    
    return Failure;
}
