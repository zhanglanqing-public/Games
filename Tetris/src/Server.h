#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <string>
#include <stdio.h>
#include <iostream>

#define BUFFER_SIZE 256

struct Server {

	
	WORD myVersionRequest;
	WSADATA wsaData;
	int err;
	SOCKET serSocket;
	SOCKADDR_IN addr;
	SOCKADDR_IN clientSocket;
	SOCKET serConn;
	char receiveBuf[BUFFER_SIZE];
	char sendBuf[BUFFER_SIZE];

	Server(std::string thisMachine) {
		for (int i = 0; i < BUFFER_SIZE; i++) {
			receiveBuf[i] = sendBuf[i] = 'o';
		}
		//include winsocket version
		myVersionRequest = MAKEWORD(1, 1);			//init_version 1.1
		err = WSAStartup(myVersionRequest, &wsaData);
		if (!err) {
			std::cout << "Socket has been opened." << std::endl;
		}
		else {
			std::cout << "Failed to open Socket." << std::endl;
			return;
		}

		// creat socket
		serSocket = socket(AF_INET, SOCK_STREAM, 0);


		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr(thisMachine.c_str());
		//addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);				//ip
		addr.sin_port = htons(3000);									//port
																		
		bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
		listen(serSocket, 10);                              // 10 , the maximum number of connections that can be listened at the same time 
		int len = sizeof(SOCKADDR);
		std::cout << "Server has been opened successfully, now waiting client to be connected..." << std::endl;
		serConn = accept(serSocket, (SOCKADDR*)&clientSocket, &len);
		if (serConn != -1) {
			std::cout << "Client has connected to this server... " << inet_ntoa(clientSocket.sin_addr) << std::endl << "Programe will start in 5 second...";
			Sleep(5000);
		}
		else {
			std::cout << "Client failed to connect this server..." << std::endl;
			return;
		}
	}
	void SendData() {
		recv(serConn, receiveBuf, BUFFER_SIZE, 0);
		send(serConn, sendBuf, BUFFER_SIZE, 0);
	}

	void Close() {
		closesocket(serConn);   
		WSACleanup();           //release the resources
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


	~Server() { Close(); }
};
