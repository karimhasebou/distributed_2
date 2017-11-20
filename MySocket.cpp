#include "MySocket.h"
#define SUCCESS 1
#define FAIL 0
using namespace std;

MySocket::MySocket(int port, std::string ip) : port(portNumber)
{
    socket.setIP(ip);
    socket.setPort(port);
    count_send = MAX_RESEND;
    count_receive = MAX_RECEIVE;
}

MySocket::~MySocket()
{
}

int MySocket::send(Message msg)
{
	std::vector<Message> msg_part = msg.divide(CHUNK_SIZE); // definition
	Message msg_void;
	socket.setTimeout(TIMEOUT);                             // definition
    	int status = SUCCESS;
	for (int i = 0; i < msg_part.size(); ++i) {
		while (status != SUCESS && count_send--) {
			socket.send(msg_part[i]);
			status = socket.receive(msg_void); // receive acknowledgment actual message need not to inspect the actual message
		}
		if (!count_send)
			return FAIL;
		resetSCount();
	}
	return SUCCESS;
}

int MySocket::receive(Message& msg)
{
    	int status = SUCESS;
	Message msg_tmp;
	socket.setTimeout(TIMEOUT); // definition
	status = socket.receive(msg_tmp);

	if (status == FAIL)
		return;

	if (msg_tmp.getMessageType() != LAST) {
		int port = msg_tmp.getPort();
		// ip = socket.getIP();                             // definition
		
        UDPSocket new_socket;	
	new_socket.setPort(port);                           // definition
	new_socket.setIP(ip);                               // definition 
	
	int status_per_part = SUCCESS;

	set<int> received_ids;
        vector<Message> msg_parts;
        do {
		status_per_part = new_socket.receive(msg_part);

		if(status_per_part == SUCCESS) {
			int id = msg_part.getPacketId();            // definition
			bool found = received_ids.find(id) != received_ids.end();
			if (!found)
			    msg_parts.push_back(msg_part);
			resetVCount();
			sendAck(new_socket);
            	}
	} while (msg_tmp.getMessageType() != LAST && count_receive--);
        if (count_receive == 0) {
            resetVCount();
            return FAIL;
        }

        Message assembled_message(msg_parts);
	msg = assembled_message;
        return SUCCESS;
	}
	else {
		msg = msg_tmp;
		return SUCCESS;
	}
}

// just felt like it needed a function
void MySocket::resetSCount()
{
    count_send = MAX_RESEND;
}

// just felt like it needed a function
void MySocket::resetVCount()
{
    count_receive = MAX_RECEIVE;
}

void MySocket::sendAck(UDPSocket socket)
{
    Messge msg; // add more initialization if needed
    msg.setMessageType(ACKNOWLEDGEMENT);                    // definition
    socket.send(msg);
}
