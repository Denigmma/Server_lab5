#include "../Include/SendGetFunc.h"

void sendFile(int ClientSocket) {
	int file_size = 0;
	std::string filename;
	std::cin >> filename;
	std::cout << std::endl;

	std::cout << "Enter the index of operation\n";
	std::string operation;
	std::cin >> operation;
	std::cout << std::endl;

	// Отправка имени файла на сервер
	send(ClientSocket, filename.c_str(), filename.size() + 1, 0);

	// Отправка operation на сервер
	send(ClientSocket, operation.c_str(), operation.size() + 1, 0);

	std::ifstream fileToSend("../../../Resource/"+filename, std::ios::binary | std::ios::ate);
	if (!fileToSend.is_open()) {
		std::cerr << "Error opening file" << std::endl;
		closesocket(ClientSocket);
		WSACleanup();
	}

	file_size = fileToSend.tellg();
	fileToSend.seekg(0, std::ios::beg);

	char sizeBuffer[sizeof(int)];
	memcpy(sizeBuffer, &file_size, sizeof(int)); // Функция memcpy копирует данные из одного места памяти в другое
	send(ClientSocket, sizeBuffer, sizeof(int), 0);

	char* fileBuffer = new char[file_size];
	fileToSend.read(fileBuffer, file_size);
	send(ClientSocket, fileBuffer, file_size, 0);
	delete[] fileBuffer;
	fileToSend.close();

	std::cout << "File sent successfully" << std::endl;
}

void getFile(int ClientSocket) {
	// Получение имени файла
	char filenameBuffer[BUFFER_SIZE];
	int bytesReceived = recv(ClientSocket, filenameBuffer, sizeof(filenameBuffer), 0);
	if (bytesReceived <= 0) {
		std::cerr << "Error: Failed to receive filename" << std::endl;
		return;
	}
	std::string filename(filenameBuffer);

	// Получение размера файла
	int fileSize = 0;
	char sizeBuffer[sizeof(int)];
	bytesReceived = recv(ClientSocket, sizeBuffer, sizeof(sizeBuffer), 0);
	if (bytesReceived <= 0) {
		std::cerr << "Error: Failed to receive file size" << std::endl;
		return;
	}
	memcpy(&fileSize, sizeBuffer, sizeof(int));

	// Получение файла
	char* fileBuffer = new char[fileSize];
	bytesReceived = recv(ClientSocket, fileBuffer, fileSize, 0);
	if (bytesReceived <= 0) {
		std::cerr << "Error: Failed to receive file data" << std::endl;
		delete[] fileBuffer;
		return;
	}

	// Сохранение файла на клиенте
	std::ofstream outputFile("../../../Resource/"+filename, std::ios::binary);
	if (!outputFile.is_open()) {
		std::cerr << "Error: Failed to open output file" << std::endl;
		delete[] fileBuffer;
		return;
	}
	outputFile.write(fileBuffer, fileSize);
	outputFile.close();
	delete[] fileBuffer;

	std::cout << "Result is received successfully" << std::endl;
}

void getMessage(int ClientSocket) {
	// Получение сообщения от сервера
	char buffer[BUFFER_SIZE];
	int bytesReceived = recv(ClientSocket, buffer, BUFFER_SIZE, 0);
	if (bytesReceived == SOCKET_ERROR) {
		std::cerr << "Error: Failed to receive data from server" << std::endl;
		closesocket(ClientSocket);
		WSACleanup();
		return;
	}
	std::string message(buffer, bytesReceived);
	std::cout << message << std::endl;
}

void sendMassage(int ClientSocket) {
	std::string msg;
	std::cin >> msg;
	send(ClientSocket, msg.c_str(), msg.size() + 1, 0);
}