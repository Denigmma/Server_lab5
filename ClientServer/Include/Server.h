#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

void server();