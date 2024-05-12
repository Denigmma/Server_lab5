#include "../include/sendLists.h"
#include "../include/Logger.h"

#include <iostream>
#include <string>

void sendHelloOpportunitiesList(int ClientSocket) {
	std::string answ = "Welcome to the image processing server\n"
		"\nServer can :\n"
		"1. Applying a Gaussian filter to the picture\n"
		"2. Alignment of the text in the picture\n"
		"3. Rotate the picture on 180 degrees\n"
		"4. Applying a black and white filter to the picture\n"
		"\nEnter the name (example.jpeg) of the picture you want to process : \n";
	send(ClientSocket, answ.c_str(), answ.size() + 1, 0);
	logMessage("HelloOpportunitiesList sent successfully");
}