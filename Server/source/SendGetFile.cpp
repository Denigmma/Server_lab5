#include "../include/SandGetFile.h"
#include "../include/Logger.h"
std::string newfilename;


void sendEditedFile(int ClientSocket) {
	int file_size = 0;
	// Отправка имени файла на клиенту
	send(ClientSocket, newfilename.c_str(), newfilename.size() + 1, 0);
	std::ifstream fileToSend("../../../resources/" + newfilename, std::ios::binary | std::ios::ate);
	if (!fileToSend.is_open()) {
		std::cerr << "Error opening edited file\n";
		return;
	}
	file_size = fileToSend.tellg();
	fileToSend.seekg(0, std::ios::beg);

	char sizeBuffer[sizeof(int)];
	memcpy(sizeBuffer, &file_size, sizeof(int));
	send(ClientSocket, sizeBuffer, sizeof(int), 0);

	char* fileBuffer = new char[file_size];
	fileToSend.read(fileBuffer, file_size);
	send(ClientSocket, fileBuffer, file_size, 0);
	delete[] fileBuffer;
	fileToSend.close();

	std::cout << "File sent successfully\n";
	logMessage("File sent to client successfully");
}

void getForEditFile(int ClientSocket) {
	// Получение имени файла
	char filenameBuffer[BUFFER_SIZE];
	int bytesReceived = recv(ClientSocket, filenameBuffer, sizeof(filenameBuffer), 0);
	if (bytesReceived <= 0) {
		std::cerr << "Error: Failed to receive filename" << std::endl;
		return;
	}
	std::string filename(filenameBuffer);
	newfilename = "edit"+filename;

	// Получение операции
	char operationBuffer[BUFFER_SIZE];
	bytesReceived = recv(ClientSocket, operationBuffer, sizeof(operationBuffer), 0);
	if (bytesReceived <= 0) {
		std::cerr << "Error: Failed to receive operation" << std::endl;
		return;
	}
	std::string operation(operationBuffer);

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

	// Сохранение файла на сервере
	std::ofstream outputFile("../../../resources/"+filename, std::ios::binary);
	if (!outputFile.is_open()) {
		std::cerr << "Error: Failed to open output file" << std::endl;
		delete[] fileBuffer;
		return;
	}
	outputFile.write(fileBuffer, fileSize);
	outputFile.close();
	delete[] fileBuffer;

	std::cout << "File received successfully" << std::endl;
	logMessage("File received from client successfully");


	switch (std::stoi(operation)) {

	case 1:
		std::cout << "gauss selected" << std::endl;
		gauss(filename,newfilename);
		logMessage("gauss selected");
		break;
	case 2:
		std::cout << "align selected" << std::endl;
		align(filename,newfilename);
		logMessage("align selected");
		break;
	case 3:
		std::cout << "rotate selected" << std::endl;
		rotate(filename,newfilename);
		logMessage("rotate selected");
		break;
	case 4:
		std::cout << "blackAndWhite selected" << std::endl;
		blackAndWhite(filename,newfilename);
		logMessage("blackAndWhite selected");
		break;
	default:
		std::cerr << "selected invalid operation" << std::endl;
		logMessage("selected invalid operation");
	}
}

void getMessage(int ClientSocket) {
	// Получение сообщения от клиента
	char buffer[BUFFER_SIZE];
	int bytesReceived = recv(ClientSocket, buffer, BUFFER_SIZE, 0);
	if (bytesReceived == SOCKET_ERROR) {
		std::cerr << "Error: Failed to receive data from server" << std::endl;
		return;
	}
	std::string message(buffer, bytesReceived);
	std::cout << message << std::endl;
	logMessage("Message from client is pleasantly successful :"+ message);
}

void sendMassage(int ClientSocket) {
	std::string msg;
	std::cin >> msg;
	send(ClientSocket, msg.c_str(), msg.size() + 1, 0);
	logMessage("Message from server has been sent successfully :"+msg);
}