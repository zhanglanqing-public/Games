#pragma once
#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<iostream>
#include<string>
#include<conio.h>

#include <string>
#define BUFFER_SIZE 256


struct Client {
	WORD versionRequired;
	WSADATA wsaData;
	int err;
	SOCKET clientSocket;		
	SOCKADDR_IN clientSockin;

	char receiveBuf[BUFFER_SIZE];
	char sendBuff[BUFFER_SIZE];

	
	Client(std::string targetServer) {
		for (int i = 0; i < BUFFER_SIZE; i++) {
			receiveBuf[i] = sendBuff[i] = 'o';
		}

		versionRequired = MAKEWORD(1, 1);		
		// sign up register of win socket and return the state
		err = WSAStartup(versionRequired, &wsaData);
		if (!err) {                               
			std::cout << LPSTR("Client socket has been opened...\n");
		} else {
			
			std::cout << "Client server failed to open...\n" << WSAGetLastError() << std::endl;
			return;
		}
		

		clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);						        
		clientSockin.sin_addr.S_un.S_addr = inet_addr(targetServer.c_str());			
		clientSockin.sin_family = AF_INET;												
		clientSockin.sin_port = htons(3000);											
																						
	}


	void try_to_connect_to_server() {
		std::cout << "Trying to connect the server..." << std::endl;
		int fail = connect(clientSocket, (SOCKADDR*)&clientSockin, sizeof(SOCKADDR));
		while (fail) {
			fail = connect(clientSocket, (SOCKADDR*)&clientSockin, sizeof(SOCKADDR));
		}
		std::cout << "Client has connected to the server, Program will begin in 5 seconds..." << std::endl;
		Sleep(5000);
	}


	void Close() {
		closesocket(clientSocket);
		if (WSACleanup() == SOCKET_ERROR) {
			std::cout << "Client socket failed to close..." << WSAGetLastError() << std::endl;
		} else {
			std::cout << "Client socket has been closed...." << std::endl;
		}
	}


	void SendData() {
		send(clientSocket, sendBuff, BUFFER_SIZE, 0);
		recv(clientSocket, receiveBuf, BUFFER_SIZE, 0);
	}


	// ============ helper - function ===============
	static std::string GetLocalIpAddress()
	{
		WORD wVersionRequested = MAKEWORD(2, 2);

		WSADATA wsaData;
		if (WSAStartup(wVersionRequested, &wsaData) != 0)
			return "";

		char local[255] = { 0 };
		gethostname(local, sizeof(local));
		hostent* ph = gethostbyname(local);
		if (ph == NULL)
			return "";

		in_addr addr;
		memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr)); // 这里仅获取第一个ip  

		std::string localIP;
		localIP.assign(inet_ntoa(addr));

		WSACleanup();
		return localIP;
	}

	~Client() { Close(); }

};