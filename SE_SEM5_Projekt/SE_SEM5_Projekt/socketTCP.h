#pragma once
#include <string>		//include libraries and header files
#include <winsock2.h>
#include <iostream>

using namespace std;		//definig namespace

class socketTCP		//defining class
{

public:
	//destructor
	~socketTCP();		//socket close

	static const int MESSAGELENGTH = 150;		//defining message length

	void linkSocket(string, int);		//connect TCP client socket according to given params

	string recvStepperData();		//read data from socket and writes them into a string

	void sendStepperData(string);		//send data to connected server

private:
	struct sockaddr_in serverAdress;		//write server data in struct

	bool connected = FALSE;		//true if connected to server

	SOCKET tcpSocket;		//socket type

	WSADATA wsaData;		//socket iostream
};
