#include "../include/Server.h"
#include "../include/Logger.h"
#include "../include/ClientHandler.h"
#include "../include/sendWebList.h"

const int DEFAULT_PORT = 8080;
const char* ADRES_CONNECTION = "127.0.0.1";
const int MAX_CONNECTION = 100;
SOCKET Connections[MAX_CONNECTION];
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
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	// Прослушивание входящих соединений
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "Failed to listen for incoming connections" << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	std::cout << "Server is running. Waiting for connections..." << std::endl;
	logMessage("Server is running. Waiting for connections on port " + std::to_string(DEFAULT_PORT));

	std::vector<std::thread> threads;

	while (true) {
		SOCKET newConnection;
		for (int i = 0; i < MAX_CONNECTION; i++) {
			if (Connections[i] == 0) {//создаем только для пустых сокетов
				newConnection = accept(serverSocket, (SOCKADDR*)&serverAddr, &addrLen); //int *sizeof(serverAddr)
				if (newConnection == 0) {
					std::cout << "Error\n";
					logMessage("Error connection");
				}
				else {
					std::cout << "Client " << i << " Connected!" << std::endl;
					logMessage("Client" + std::to_string(i) + "Connected");
					// // Блокировка мьютекса
					std::lock_guard<std::mutex> lock(mtx);
					// Обработка клиента в отдельном потоке
					threads.emplace_back(ClientHandler, newConnection);
				}
			}
		}
	}
	for (auto& thread : threads) {
		thread.join();
	}
}