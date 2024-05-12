#include "../include/ClientHandler.h"
#include "../include/sendWebList.h"
const int BUFFER_SIZE = 1024;

void ClientHandler(int newConnection) {
	// Отправляем клиенту Web-интерфейс
	sendWebList(newConnection);
	bool isconnect = true;

	while (isconnect) {
		std::string request; // Создаем пустую строку для хранения запроса
		char buffer[1024]; // Буфер для чтения данных
		int bytesReceived; // Хранение количества считанных байт

		while ((bytesReceived = recv(newConnection, buffer, BUFFER_SIZE, 0)) > 0) {
			request.append(buffer, bytesReceived); // Добавляем считанные данные к общему запросу
			// Если считаны все данные, выходим из цикла чтения
			// это значит, что больше данных нет, и мы выходим из цикла
			if (bytesReceived < BUFFER_SIZE) {
				break;
			}
		}

		if (bytesReceived > 0) {
			// Анализируем запрос
			if (!request.empty()) {
				if (request.find("POST") != std::string::npos) {
					if (request.find("/upload_image") != std::string::npos) {
						// Вызываем функцию фильтра
						std::cout << "Загрузку картинки выбрали" << std::endl;

						//upload_image();
					}
					if (request.find("/filter_gauss") != std::string::npos) {
						// Вызываем функцию фильтра
						//applyFilter();
						std::cout << "Гаусса выбрали" << std::endl;
					}
					else if (request.find("/scale_image") != std::string::npos) {
						// Вызываем функцию масштабирования
						//scaleImage();
						std::cout << "масштабирование выбрали" << std::endl;
					}
					else if (request.find("/align_text") != std::string::npos) {
						// Вызываем функцию выравнивания текста
						//alignText();
						std::cout << "выравнивание текста выбрали" << std::endl;
					}
					else if (request.find("/rotate_image") != std::string::npos) {
						// Вызываем функцию поворота изображения
						//rotateImage();
						std::cout << "поворот выбрали" << std::endl;
					}
					else if (request.find("/black_white") != std::string::npos) {
						// Вызываем функцию поворота изображения
						//rotateImage();
						std::cout << "ЧБ выбрали" << std::endl;
					}

				}
				else if (request.find("GET") != std::string::npos) {
					if (request.find("/download_image") != std::string::npos) {
						// Обработка GET запроса
						std::cout << "скачать изо выбрали" << std::endl;

						// Открытие файла с изображением
						std::ifstream imageFile("output.jpeg", std::ios::binary | std::ios::ate);
						if (!imageFile.is_open()) {
							std::cerr << "Error opening image file\n";
							closesocket(newConnection);
							WSACleanup();
							break;
						}

						// реализация отправки
						// Получение размера файла
						int file_size = imageFile.tellg();
						imageFile.seekg(0, std::ios::beg);

						// Отправка изображения по сети
						char* fileBuffer = new char[file_size];
						imageFile.read(fileBuffer, file_size);
						send(newConnection, fileBuffer, file_size, 0);

						delete[] fileBuffer;
						imageFile.close();

						std::cout << "Image sent successfully\n";

						// Закрытие сокетов и очистка Winsock
						closesocket(newConnection);
						WSACleanup();

						//sendFileToClient();
						//isconnect = false;
					}
				}
			}
		}
	}
}


//void ClientHandler(int newConnection){
//	// Отправляем клиенту Web-интерфейс
//	sendWebList(newConnection);
//
//	std::string request; // Создаем пустую строку для хранения запроса
//	char buffer[1024]; // Буфер для чтения данных
//	int bytesReceived = recv(newConnection, buffer, BUFFER_SIZE, 0); // Хранение количества считанных байт
//	
//	// анализиуруем запрос, определяем метод 
//	// if post{
//	// if (apply_filter){
//	//		вызываем функцию фильтра}
//	//else if(scaleImage){
//	// вызываем функцию масштабирования}
//	//и тд...
//	// else{ - это гет запрос
//	// отправляем файл клиенту, вызываем функцию отправки файла
//
//}
//
//void handleGetRequest(int newConnection) {
//   
//}
//
//void handlePostRequest(int newConnection, const std::string& requestData) {
//
//}
//
//void handleImageUpload(int newConnection, const std::string& requestData) {
//    
//}