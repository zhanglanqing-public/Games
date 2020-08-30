
// #define SERVER

#ifdef SERVER
#include "Server.h"
#endif // SEVER

#ifndef SERVER
#include "Client.h"
#endif // !SERVER

#include "global.h"
#include "Buffer.h"
#include "Heap.h"
#include "Objmanager.h"


void ShowInfo() {
	system("cls");
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "					Tetris				  " << std::endl;
	std::cout << "				Author: Zhanglanqing           " << std::endl << std::endl;
	std::cout << "			Press Any Key To continue...      " << std::endl;
	getch();
}

#ifdef SERVER

void Start() {
	system("cls");
	Server ser(Server::GetLocalIpAddress());
	auto rec = std::string(240, 'o');
	ser.SendData();
	rec = std::string(ser.receiveBuf, ser.receiveBuf + 240);
	system("cls");

	Buffer* buffer = new Buffer();
	Heap* heap = new Heap();
	ObjectManager* manager = new ObjectManager(heap, buffer);
	while (manager->gameOver == false) {
		if (manager->ObjValid() == false) {
			manager->Init();
		}
		manager->MoveDown();
		manager->Delay();
		manager->Print(rec);

		// write the data which will be send away
		auto stringOut = buffer->EncodeStateToString();

		if (manager->gameOver) {
			system("cls");
			std::cout << "You lose" << std::endl;
			stringOut = std::string(240, 'x');
		}

		copy(stringOut.begin(), stringOut.end(), ser.sendBuf);
		ser.SendData();
		rec = std::string(ser.receiveBuf, ser.receiveBuf + 240);

		if (rec == std::string(240, 'x')) {
			system("cls");
			std::cout << "You Win" << std::endl;
			manager->gameOver = true;
		}
	}
	delete buffer;
	delete heap;
	delete manager;
}

#else

void Start() {
	using namespace std;
	system("cls");
	string target_ip;
	cout << "As a client, please enter the Server's ip address. (e.g. 192.168.0.2)" << endl;
	cin >> target_ip;
	Client client(target_ip);
	// Client client(Client::GetLocalIpAddress());
	client.try_to_connect_to_server();
	string send_away = string(240, 'o');
	string rec = string(240, 'o');
	client.SendData();
	rec = string(client.receiveBuf, client.receiveBuf + 240);
	system("cls");

	Buffer* buffer = new Buffer();
	Heap* heap = new Heap();
	ObjectManager* manager = new ObjectManager(heap, buffer);
	while (manager->gameOver == false) {
		if (manager->ObjValid() == false) {
			manager->Init();
		}
		manager->MoveDown();
		manager->Delay();
		manager->Print(rec);

		// write the data which will be send away
		string stringOut = buffer->EncodeStateToString();

		if (manager->gameOver) {
			system("cls");
			cout << "You lose" << endl;
			stringOut = string(240, 'x');
		}


		copy(stringOut.begin(), stringOut.end(), client.sendBuff);
		client.SendData();
		rec = string(client.receiveBuf, client.receiveBuf + 240);

		if (rec == string(240, 'x')) {
			system("cls");
			cout << "You Win" << endl;
			manager->gameOver = true;
		}

	}
	delete buffer;
	delete heap;
	delete manager;
}
#endif // !SERVER



#define DEFAULT_IP "127.0.0.1"  
#define MAX_PATH 260  



int main() {
	ShowInfo();
	Start();
	getchar();
}