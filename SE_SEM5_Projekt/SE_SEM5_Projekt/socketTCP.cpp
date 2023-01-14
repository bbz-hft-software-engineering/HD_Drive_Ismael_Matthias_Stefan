
#pragma warning(disable:4996) 
#pragma comment(lib,"ws2_32.lib")

#include "socketTCP.h"		//include header file

using namespace std;		//defining namespace

socketTCP::~socketTCP()
{ 
	closesocket(tcpSocket);		//closing socket
	WSACleanup();
	cout << "***********************************************************************" << endl;
	cout << "Socket closed succesfully." << endl;
	cout << "***********************************************************************" << endl;

}


void socketTCP::linkSocket(string ipAdress, int port)
{
	bool fail = false;

	if (!connected)		//only start connecting if not already connected
	{
		serverAdress.sin_family = AF_INET;		//set to IPv4
		serverAdress.sin_port = htons(port);		//set port
		serverAdress.sin_addr.S_un.S_addr = inet_addr(ipAdress.c_str());		//set IP adress

		cout << "***********************************************************************" << endl;
		cout << "Initialize Winsock...";
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)		//initializing Winsock
		{
			cout << "Error" << endl << "WSAStartup failed: " << WSAGetLastError() << endl;
			fail = true;
			EXIT_FAILURE;
		}

		if (fail == false)
		{
			cout << "OK" << endl;
			cout << "Initializing socket, type: stream-socket with TCP protocol";
		}

		if ((tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)		//initializing TCP stream socket
		{
			cout << "Error" << endl << "Initalizing socket failed: " << WSAGetLastError() << endl;
			fail = true;
			EXIT_FAILURE;
		}

		if (fail == false)
		{
			cout << " OK" << endl;
			cout << "Server IP: " << ipAdress << " | Port: " << port << endl;
			cout << "Connecting to server...";
		}

		if (connect(tcpSocket, (struct sockaddr*)&serverAdress, sizeof(serverAdress)) == INVALID_SOCKET)		//connect to server
		{
			cout << "Error" << endl << "Connection to server failed: " << WSAGetLastError() << endl;
			fail = true;
			EXIT_FAILURE;
		}

		if (fail == false)
		{
			cout << " OK" << endl;
			cout << "Done! Cennection succesfull!" << endl;
			cout << "\"Communication preescaler\" about 200 is recomended" << endl;
			cout << "(Set in browser: http://" << ipAdress << "/index.html?ip  >Save>Restart)" << endl;
			cout << "***********************************************************************" << endl;

			connected = TRUE;		//set connected to true
		}
	}
}

string socketTCP::recvStepperData()
{
	string receivedData;
	receivedData.resize(MESSAGELENGTH);		//set string to matching length

	if (connected)		//check connection state and only send/receive data when connected
	{

		char tempMessage[MESSAGELENGTH];		//create local array to store received string temporarily

		if (recv(tcpSocket, tempMessage, MESSAGELENGTH, 0) == SOCKET_ERROR)		//receive data
		{
			cout << "Socket error; failed to receive data: " << WSAGetLastError() << endl;
			EXIT_FAILURE;
		}

		string tempString(tempMessage);		//turns array to string
		receivedData = tempString;
	}

	return receivedData;
}

void socketTCP::sendStepperData(string data) {
	if (send(tcpSocket, data.c_str(), strlen(data.c_str()), 0) == SOCKET_ERROR)		//send data
	{
		cout << "Socket error; failed to send: " << WSAGetLastError() << endl;
		cout << "Somehow you or the program f*cked up! Check the README.md for help...";
		_set_abort_behavior(0, _WRITE_ABORT_MSG);		//surpress abort message window
		abort();		//exit program
	}
}