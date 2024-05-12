# **Image_processing_server**
Многопоточный сервер по обработке изображений

Лабораторная работа номер 5 (1 курс 2 семестр) (СПБГУ МатМех)

Выполнил : Мурадян Денис Степанович

## Контекст работы 
Данный проект представляет собой реализацию многопоточного сервера, для обработки изображений с помощью реализованных функций, таких как:
- Наложение на изображение фильтра Гаусса
- Выравнивание текста на изображении
- Поворот изображения на 180 градусов
- Наложение черно-белого фильтра
> Примечание: Алгоритм функции **(Выравнивание текста на изображении)** был разработан мною на олимпиаде «Petropolitan Science (Re)Search» в 2023/24 учебном году. По предмету «Вычислительные технологии» для обучающихся и выпускников бакалавриата.

## Использование сервера:
Запустите `Server` и `ClientServer`:
>(инструкцию по сборке и запуске вы сможете найти ниже)

После запуска `Server`, а так же после успешного подключения клиента, в терминальном окне вы увидите:
```
Server is running. Waiting for connections...
Client connected 
```
В терминальном окне `ClientServer` вы увидите:
```
Welcome to the image processing server
Server can :
1. Applying a Gaussian filter to the picture
2. Alignment of the text in the picture
3. Rotate the picture on 180 degrees
4. Applying a black and white filter to the picture

Enter the name (example.jpeg) of the picture you want to process :
```
После чего следует ввести имя файла, которое вы хотите обработать.

```Enter the index of operation :```

Далее следует выбрать индекс операции, который вы хотите произвести.


В случае успешной обработки изображения, вы получите сообщение:


```Result is received successfully```


Что означает, что файл успешно обработан и сохранен в  папке ` Resource `.

>Обратите внимание, что обработанный файл сохраняется с приставкой `edit` к вашему исходному (отправленному на сервер) файлу.

## Структура проекта
### Server:
- `resources` содержит файлы, принятые и обработанные сервером, а так же log файл работы сервера.
- `include` содержит .h файлы, определения функций работы сервера.
> `FunctionsServerh` содержит .h файлы, определения функций по обработке изображений.

-  `source` содержит .cpp файлы, реализацию функций работы сервера.
> `FunctionsServer` содержит реализацию функций по обработке изображений.

### ClientServer:
- `Resource` содержит файлы, отправленные клиентом и отправленные сервером.
- `Include` содержит .h файлы, определения функций работы Клиента-сервера.
-  `Source` содержит .cpp файлы, реализацию функций работы Клиента-сервера.
## Используемые инструменты и библиотеки.
- Язык программирования с++.
- Встроенные библиотеки:
1. iostream
2. vector
3. fstream
4. ctime
5. algorithm
6. sstream

- Библиотеки для работы с сокетом:
1. winsock2.h
2. ws2tcpip.h

- Библиотеки  для работы с изображениями:
STB_IMAGE_WRITE_IMPLEMENTATION
1. “stb_image.h”
2. “stb_image_write.h”

- Библиотеки для работы с многопоточностью:
1. thread
2. mutex

- Параллельность
  
Сервер способен параллельно обрабатывать запросы от разных подключенных клиентов одновременно. Когда новый клиент подключается, для него создается отдельный поток, который обрабатывает его запросы независимо от других клиентов. Так же, сервер защищен от конфликтов при одновременном доступе к общим данным. Эту защиту обеспечитывает использование `mutex` mtx. (Синхронизация доступа к ресурсам сервера из разных потоков)

## Google Code Style
Код проекта соответствует [Google Code Style](https://google.github.io/styleguide/cppguide.html).
## Конфигурация, сборка и запуск
### В репозитории имеются три папки:
- `Server`
> Реализация работы сервера

- `ClientServer`
> Реализация работы клиента

- `Server_HTTP(demo)`
> Реализация работы сервера с подгрузкой web-интерфейса и общением с клиентом через http протокол. 

> Примечание: Данная версия работает нестабильно. Ограничена работа некоторых функций.

Проект собран с помощью CMake.

В каждой папке вы можете найти CMakeLists.txt, относящийся к конкретно выбранной области.

Чтобы запустить сервер, скомпилируйте и запустите исполняемый файл.
> Пример с `Server`:

build/CMakeLists.txt:
```
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Server")

add_executable (Server 
"Source/main.cpp" 
"Include/Server.h" 
"Source/Server.cpp" 
"include/Logger.h" 
"source/Logger.cpp" 
"source/ClientHandler.cpp" 
"include/ClientHandler.h" 
"source/sendLists.cpp" 
"include/sendLists.h" 
"source/FunctionsServer/gauss.cpp"
"source/SendGetFile.cpp" 
"source/FunctionsServer/align.cpp" 
"source/FunctionsServer/rotate.cpp" 
"include/FunctionsServerh/align.h" 
"include/FunctionsServerh/rotate.h"
"include/FunctionsServerh/blackwhite.h"
"source/FunctionsServer/blackwhite.cpp" 
"include/FunctionsServerh/stb_image_write.h"
"include/FunctionsServerh/stb_image.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Server PROPERTY CXX_STANDARD 20)
endif()
```
Сборка при помощи CMake:
```
mkdir build
cd build
cmake build .
make 
```
Запуск
``` ./Server ```



