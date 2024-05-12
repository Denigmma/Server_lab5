#include "../include/ClientHandler.h"
#include "../include/sendLists.h"
#include "../include/SandGetFile.h"


void ClientHandler(int ClientSocket) {
	sendHelloOpportunitiesList(ClientSocket);
	getForEditFile(ClientSocket);
	sendEditedFile(ClientSocket);

}