
#include <winsock2.h>
#include<string>
#include<windows.h>
#include <process.h>
#include<vector>
#include<map>
#include <iostream>
#include <stdio.h>
#include <queue>
#include<fstream>
#include "Package.h"
#pragma comment(lib, "Ws2_32.lib")

#define PATH_USES			"./Users.txt"
#define TCP_SERVER_PORT     8080
#define TCP_SERVER_ADDRESS  "127.0.0.1"

#define MAX_LISTEN_QUEUE	10

//SOCKET ListenSocket;
//SOCKET AcceptSocket;
//SOCKADDR_IN InternetAddr;
//WSADATA wsaData;
//INT Ret;
//FD_SET WriteSet;
//FD_SET ReadSet;
//DWORD i;
//DWORD Total;
//ULONG NonBlock;
//DWORD Flags;
//DWORD SendBytes;
//DWORD RecvBytes;
//HANDLE hdAcceptConnect;
HANDLE hdSend;
HANDLE hdReceive;

struct User
{
	std::string account;
	int id;
};

std::map<std::string, User> users ;

unsigned int __stdcall receiveThread(void* arg);
unsigned int __stdcall sendThread(void* arg);

//unsigned int __stdcall acceptConnect(void* arg);
//unsigned int __stdcall sendClient(void* arg);
//unsigned int __stdcall receiveClient(void* arg);
void loadUserAccounts();
void processData(char*, char*);
int Receive(SOCKET, char*, int, int);
int Send(SOCKET, char*, int, int);


int main()
{
	//Step 1: Initiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData))
		std::cout << "Version is not supported\n";

	//Step 2: Construct socket	
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//Step 3: Bind address to socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(TCP_SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(TCP_SERVER_ADDRESS);

	if (bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr)))
	{
		std::cout << "Error! Cannot bind this address.\n";
		return 0;
	}

	//Step 4: Listen request from client
	if (listen(listenSock, 10)) {
		std::cout << "Error! Cannot listen.";
		return 0;
	}

	std::cout << "Server started!\n";

	SOCKET client[FD_SETSIZE], connSock;
	fd_set readfds, initfds; //use initfds to initiate readfds at the begining of every loop step
	sockaddr_in clientAddr;
	int ret, nEvents, clientAddrLen;
	unsigned char rcvBuff[BUFFER_SIZE], sendBuff[BUFFER_SIZE];

	for (int i = 0; i < FD_SETSIZE; i++)
		client[i] = 0;	// 0 indicates available entry

	FD_ZERO(&initfds);
	FD_SET(listenSock, &initfds);

	//Step 5: Communicate with clients
	while (true) {
		readfds = initfds;		/* structure assignment */
		nEvents = select(0, &readfds, 0, 0, 0);
		if (nEvents < SOCKET_ERROR) {
			std::cout << "\nError! Cannot poll sockets: " << WSAGetLastError();
			break;
		}

		//new client connection
		if (FD_ISSET(listenSock, &readfds)) {
			clientAddrLen = sizeof(clientAddr);
			if ((connSock = accept(listenSock, (sockaddr*)&clientAddr, &clientAddrLen)) < 0) {
				std::cout << "\nError! Cannot accept new connection: " << WSAGetLastError();
				break;
			}
			else {
				std::cout << "You got a connection from %s\n" << inet_ntoa(clientAddr.sin_addr); /* prints client's IP */

				int i;
				for (i = 0; i < FD_SETSIZE; i++)
					if (client[i] == 0) {
						client[i] = connSock;
						FD_SET(client[i], &initfds);
						break;
					}

				if (i == FD_SETSIZE) {
					std::cout << "\nToo many clients.";
					closesocket(connSock);
				}

				if (--nEvents == 0)
					continue; //no more event
			}
		}

		//receive data from clients
		for (int i = 0; i < FD_SETSIZE; i++) {
			if (client[i] == 0)
				continue;

			if (FD_ISSET(client[i], &readfds)) {
				ret = Receive(client[i], rcvBuff, BUFFER_SIZE, 0);
				if (ret <= 0) {
					FD_CLR(client[i], &initfds);
					closesocket(client[i]);
					client[i] = 0;
				}
				else if (ret > 0) {
					processData(rcvBuff, sendBuff);
					Send(client[i], sendBuff, ret, 0);
				}
			}

			if (--nEvents <= 0)
				continue; //no more event
		}

	}
	//if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
	//{
	//	printf("WSAStartup() failed with error %d\n", Ret);
	//	WSACleanup();
	//	return 1;
	//}
	//else
	//	printf("WSAStartup() is fine!\n");

	////
	//if ((ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	//{
	//	printf("WSASocket() failed with error %d\n", WSAGetLastError());
	//	return 1;
	//}
	//else
	//	printf("WSASocket() is OK!\n");

	//InternetAddr.sin_family = AF_INET;
	//InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//InternetAddr.sin_port = htons(TCP_SERVER_PORT);



	//if (bind(ListenSocket, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	//{
	//	printf("bind() failed with error %d\n", WSAGetLastError());
	//	return 1;
	//}
	//else
	//	printf("bind() is OK!\n");

	//if (listen(ListenSocket, MAX_LISTEN_QUEUE))
	//{
	//	printf("listen() failed with error %d\n", WSAGetLastError());
	//	return 1;
	//}
	//else
	//	printf("listen() is OK!\n");

	//NonBlock = 1;
	//if (ioctlsocket(ListenSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
	//{
	//	printf("ioctlsocket() failed with error %d\n", WSAGetLastError());
	//	return 1;
	//}
	//else
	//	printf("ioctlsocket() is OK!\n");

	//hdAcceptConnect = (HANDLE)_beginthreadex(NULL, NULL, &acceptConnect, NULL, NULL, NULL);
	//hdSend = (HANDLE)_beginthreadex(NULL, NULL, &sendThread, NULL, NULL, NULL);
	//hdReceive = (HANDLE)_beginthreadex(NULL, NULL, &receiveThread, NULL, NULL, NULL);

	//WaitForSingleObject(hdAcceptConnect, INFINITE);
	//WaitForSingleObject(hdSend, INFINITE);
	//WaitForSingleObject(hdReceive, INFINITE);

	closesocket(listenSock);
	WSACleanup();
	return 0;
}
//
//unsigned int __stdcall acceptConnect(void* arg)
//{
//
//	return 0;
//}

unsigned int __stdcall receiveThread(void* arg)
{
	return 0;

}unsigned int __stdcall sendThread(void* arg)
{
	return 0;
}

//unsigned int __stdcall receiveClient(void* arg)
//{
//	return 0;
//}
void processData(char* in, char* out) {
	memcpy(out, in, BUFFER_SIZE);
}

/* The recv() wrapper function */
int Receive(SOCKET s, char* buff, int size, int flags) {
	int n;

	n = recv(s, buff, size, flags);
	if (n == SOCKET_ERROR)
		printf("Error: %", WSAGetLastError());

	return n;
}

/* The send() wrapper function*/
int Send(SOCKET s, char* buff, int size, int flags) {
	int n;

	n = send(s, buff, size, flags);
	if (n == SOCKET_ERROR)
		std::cout << "Error: %" << WSAGetLastError();

	return n;
}

void loadUserAccounts()
{
	std::ifstream file(PATH_USES, std::ios::in);
	int n;
	file >> n;
	for (int i = 0; i < n; ++i)
	{
		std::string account, password;
		file >> account >> password;
		users[account] = { password, 0};
	}
}