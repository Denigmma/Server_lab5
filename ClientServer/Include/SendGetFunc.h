#include <iostream>
#include <fstream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define BUFFER_SIZE 1024


void sendFile(int ClientSocket);
void getFile(int ClientSocket);

void getMessage(int ClientSocket);
void sendMassage(int ClientSocket);