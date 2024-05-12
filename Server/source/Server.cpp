#include "../include/Server.h"
#include "../include/Logger.h"
#include "../include/ClientHandler.h"
#include "../include/sendLists.h"

const int DEFAULT_PORT = 8080;
const char* ADRES_CONNECTION = "127.0.0.1";
const int MAX_CONNECTION = 100;

std::mutex mtx;

void Server() {
	WSADATA wsaData;
	SOCKET serverSocket;
	struct sockaddr_in serverAddr, clientAddr;
	int addrLen = sizeof(clientAddr);

	// Инициализация библиотеки Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Failed to initialize Winsock" << std::endl;
		logMessage("Failed to initialize Winsock");
		return;
	}

	// Создание сокета
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		std::cerr << "Failed to create socket" << std::endl;
		logMessage("Failed to create socket");
		WSACleanup();
		return;
	}

	// Настройка адреса сервера
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ADRES_CONNECTION);
	serverAddr.sin_port = htons(DEFAULT_PORT);

	// Привязка сокета к адресу и порту
	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		std::cerr << "Failed to bind socket to address and port" << std::endl;
		logMessage("Failed to bind socket to address and port");
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	// Прослушивание входящих соединений
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "Failed to listen for incoming connections" << std::endl;
		logMessage("Failed to listen for incoming connections");
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	std::cout << "Server is running. Waiting for connections..." << std::endl;
	logMessage("Server is running. Waiting for connections on port " + std::to_string(DEFAULT_PORT));

	while (true) { 
		SOCKET ClientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen); // Принятие клиентского подключения
		if (ClientSocket == INVALID_SOCKET) { 
			std::cerr << "Accept client failed"<<std::endl;
			logMessage("Accept client failed");
			return;
		}
		std::cout << "Client connected" << std::endl;
		logMessage("Client connected");

		std::lock_guard<std::mutex> lock(mtx);
		std::thread clientThread(ClientHandler, ClientSocket); 
		clientThread.detach();
	}

	closesocket(serverSocket);
	WSACleanup();
	logMessage("Server is disabled");
}