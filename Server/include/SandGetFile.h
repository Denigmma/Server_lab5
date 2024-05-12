#include <iostream>
#include <fstream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define BUFFER_SIZE 1024

#include "../include/FunctionsServerh/gauss.h"
#include "../include/FunctionsServerh/align.h"
#include "../include/FunctionsServerh/blackwhite.h"
#include "../include/FunctionsServerh/rotate.h"

void sendEditedFile(int ClientSocket);
void getForEditFile(int ClientSocket);

void getMessage(int ClientSocket);
void sendMassage(int ClientSocket);