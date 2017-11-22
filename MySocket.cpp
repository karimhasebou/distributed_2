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
    
    int requestsCount = 0;
    Status receiveStatus = Pending;
    
    Packet receivedPacket;
    
    while(receiveStatus != Success &&
          receiveStatus != StreamFailure &&
          requestsCount++ < MAX_REQUESTS) {
        
        rpcSocket.sendPacket(sentPacket);
        
        receiveStatus = receive(rpcSocket, receivedPacket);
        
    }
    
    return receivedPacket.getMessage();
}

int MySocket::recvFrom(Packet & receivedPacket) {
    
    return mainSocket.recievePacket(receivedPacket);
    
}

int MySocket::reply(const Packet& sentPacket) {
    
    UDPSocket replySocket;
    replySocket.bind(0);
    
    std::vector<Message> dividedMessage = sentPacket.getMessage().divide(CHUNK_SIZE);
    
    Packet partitionPacket = sentPacket;
    bool stopProcess = false;
    
    for (int part = 0; part < dividedMessage.size() && stopProcess; part++) {
        
        int sentPacketCount = 0;
        partitionPacket.setMessage(dividedMessage[part]);
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

Status MySocket::receive(UDPSocket & socket, const Packet & packet) {
    
    socket.setTimeOut(TIMEOUT);
    
    Packet receivedPacket;
    
    int status = socket.recievePacket(receivedPacket);
    
    if (status == -1) {
        return PacketFailure;
    }
    
    vector<Message> messages;
    
    Message fullMessage;
    
    Message ackMessage;
    
    ackMessage.setMessageType(Acknowledgement);
    
    Packet ackPacket;
    ackPacket.setMessage(ackMessage);
    
    do {
        
        messages.push_back(receivedPacket.getMessage());
        
        socket.sendPacket(ackPacket);
        
        if (receivedPacket.getMessage().getMessageType() == Last) {
            
            fullMessage.combine(messages);
            
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

//int MySocket::send(const Packet& packet)
//{
//    
//    UDPSocket newSocket;
//    newSocket.bind(0);
//    
//	std::vector<Message> dividedMessage = message.divide(CHUNK_SIZE);
//    
//	Message msg_void;
//	newSocket.setTimeOut(TIMEOUT);
//    
//    int status = FAIL;
//	for (int i = 0; i < dividedMessage.size(); ++i) {
//        
//        int sendCount = 0;
//        
//		while (status != SUCCESS && sendCount < MAX_RESEND) {
//			socket.send(dividedMessage[i]);
//			status = socket.receive(msg_void); // receive acknowledgment actual message need not to inspect the actual message
//            sendCount++;
//		}
//        
//		if (status != SUCCESS)
//			return FAIL;
//	}
//    
//	return SUCCESS;
//}
//
//int MySocket::receive(Message& msg)
//{
//    int status = FAIL;
//	Message msg_tmp;
//	socket.setTimeOut(TIMEOUT); // definition
//	status = socket.receive(msg_tmp);
//
//	if (status == FAIL)
//		return;
//
//	if (msg_tmp.getMessageType() != LAST) {
//		int port = msg_tmp.getPort();
//		// ip = socket.getIP();                             // definition
//		
//        UDPSocket new_socket;	
//	new_socket.setPort(port);                           // definition
//	new_socket.setIP(ip);                               // definition 
//	
//	int status_per_part = SUCCESS;
//
//	set<int> received_ids;
//        vector<Message> msg_parts;
//        do {
//		status_per_part = new_socket.receive(msg_part);
//
//		if(status_per_part == SUCCESS) {
//			int id = msg_part.getPacketId();            // definition
//			bool found = received_ids.find(id) != received_ids.end();
//			if (!found)
//			    msg_parts.push_back(msg_part);
//			resetVCount();
//			sendAck(new_socket);
//            	}
//	} while (msg_tmp.getMessageType() != LAST && count_receive--);
//        if (count_receive == 0) {
//            resetVCount();
//            return FAIL;
//        }
//
//        Message assembled_message(msg_parts);
//	msg = assembled_message;
//        return SUCCESS;
//	}
//	else {
//		msg = msg_tmp;
//		return SUCCESS;
//	}
//}

