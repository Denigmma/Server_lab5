#include "../Include/Server.h"
#include "../Include/SendGetFunc.h"
const char* ADRES_CONNECTION = "127.0.0.1";



void server(){
	WSADATA wsaData;
	SOCKET ClientSocket;
	struct sockaddr_in clientAddr;
	struct sockaddr_in serverAddr;
	int addrLen = sizeof(clientAddr);

	// Инициализация библиотеки Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Failed to initialize Winsock" << std::endl;
		return;
	}

	// Создание сокета
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		std::cerr << "Failed to create socket" << std::endl;
		WSACleanup();
		return;
	}

	// Настройка адреса сервера
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_addr.s_addr = inet_addr(ADRES_CONNECTION);
	clientAddr.sin_port = htons(PORT);

	// Функция inet_pton преобразует IP-адрес в структуру sockaddr_in
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, ADRES_CONNECTION, &serverAddr.sin_addr) <= 0) {
		std::cerr << "Invalid address/ Address not supported\n";
		closesocket(ClientSocket);
		WSACleanup();
		return;
	}

	// Подключение к серверу
	if (connect(ClientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		std::cerr << "Connection failed\n";
		closesocket(ClientSocket);
		WSACleanup();
		return;
	}

		getMessage(ClientSocket);
		sendFile(ClientSocket);
		getFile(ClientSocket);

	closesocket(ClientSocket);
	WSACleanup();
}