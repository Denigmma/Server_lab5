#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

void Server();