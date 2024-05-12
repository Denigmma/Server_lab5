#include "../include/sendWebList.h"


#include <iostream>
#include <string>

void sendWebList(int newConnection) {
    // Создаем заголовки
    std::string headers = "HTTP/1.1 200 OK\r\n";
    headers += "Content-Type: text/html\r\n";

    // Создаем HTML-страницу
    std::string response = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Image Processing Server</title>
            <style>
                body {
                    text-align: center;
                }

                button {
                    margin: 10px;
                    padding: 15px 30px;
                    font-size: 18px;
                }
            </style>
        </head>
        <body>
            <h2>Image Processing Server</h2>

            <!-- Форма для загрузки изображения -->
            <form id="uploadForm" method="POST" action="/upload_image">
                <button type="submit">Загрузить изображение</button>
            </form>

            <hr> <!-- Горизонтальная линия -->

            <!-- Формы для обработки изображения -->
            <form id="filter_gauss" method="POST" action="/filter_gauss">
                <button type="submit">Применить гауссовский фильтр</button>
            </form>

            <form id="scale_image" method="POST" action="/scale_image">
                <button type="submit">Изменить размер изображения</button>
            </form>

            <form id="align_text" method="POST" action="/align_text">
                <button type="submit">Выровнять текст</button>
            </form>

            <form id="rotate_image" method="POST" action="/rotate_image">
                <button type="submit">Повернуть изображение</button>
            </form>

            <hr> <!-- Горизонтальная линия -->

            <!-- Кнопка для получения результата -->
            <button id="getResultBtn" onclick="document.getElementById('result').innerHTML = '<p>Результат обработки изображения</p>';">Показать результат</button>

            <!-- Место для отображения результата -->
            <div id="result"></div>
        </body>
        </html>
    )";

    // Определяем размер содержимого
    headers += "Content-Length: " + std::to_string(response.length()) + "\r\n";
    headers += "\r\n";

    // Отправляем заголовки клиенту
    send(newConnection, headers.c_str(), headers.length(), 0);

    // Отправляем HTML-страницу
    send(newConnection, response.c_str(), response.length(), 0);
}



//void sendWebList(int newConnection) {
//    // Создаем заголовки
//    std::string headers = "HTTP/1.1 200 OK\r\n";
//    headers += "Content-Type: text/html\r\n";
//
//    // Читаем содержимое HTML файла в строку
//    std::ifstream htmlFile("../../../Resources/web_interface.html");
//    if (!htmlFile.is_open()) {
//        std::cout << "Ошибка открытия HTML файла" << std::endl;
//        return;
//    }
//
//    std::stringstream buffer;
//    buffer << htmlFile.rdbuf();
//    std::string htmlContent = buffer.str();
//
//    // Определяем размер содержимого
//    headers += "Content-Length: " + std::to_string(htmlContent.length()) + "\r\n";
//    headers += "\r\n";
//
//    // Отправляем заголовки клиенту
//    send(newConnection, headers.c_str(), headers.length(), 0);
//
//    // Отправляем содержимое HTML файла
//    send(newConnection, htmlContent.c_str(), htmlContent.length(), 0);
//}

//void sendWebList(int newConnection) {
//    // Отправляем заголовки
//    std::string headers = "HTTP/1.1 200 OK\r\n";
//    headers += "Content-Type: text/html\r\n\r\n";
//    send(newConnection, headers.c_str(), headers.length(), 0);
//
//    // Отправляем содержимое HTML файла
//    std::ifstream htmlFile("../../../Resources/web_interface.html");
//    if (!htmlFile.is_open()) {
//        std::cout << "Ошибка открытия HTML файла" << std::endl;
//        return;
//    }
//
//    // Читаем содержимое HTML файла в строку
//    std::stringstream buffer;
//    buffer << htmlFile.rdbuf();
//    std::string htmlContent = buffer.str();
//
//    //// Отправляем содержимое HTML файла клиенту
//    send(newConnection, htmlContent.c_str(), htmlContent.length(), 0);
//}
