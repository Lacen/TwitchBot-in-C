#include "Authenticate.h"
#include "Commands.h"
#include "Parser.h"
#include "SocketFunctions.h"
#include "TwitchBot.h"
#include "TwitchbotMacros.h"


/*
This class intalize a socket to Twitch along with method to allow send and recv from twitch
*/





SOCKET Initialize() {

	//variable
	struct addrinfo hints, *res;
	WSADATA data;

	// Initalize WSA
	int WSAERR = WSAStartup(MAKEWORD(2, 2),&data);
	if (WSAERR != 0) {
		printf("Failed Error Code :%d", WSAGetLastError());
		exit(0);
	}

	//Fill in addrinfo of hint and memset
	memset(&hints, 0, sizeof(hints)); // Intialize and set everything to null
	hints.ai_family = AF_INET; // The address family to be used by the socket which in this case is IPV4	
	hints.ai_socktype = SOCK_STREAM; // The socket type which in this case is TCP		
	hints.ai_protocol = 0; // The protocol type which is set to 0 to allow service to assign instead of manual

	
	int addrinfores = getaddrinfo(TWITCH_ADDRESS, TWITCH_PORT, &hints, &res); //Convert hostname into ipaddress using getaddrinfo
	
	//Error Check
	if (addrinfores != 0) {
		printf("There is a error in acquiring the IP address");
		WSACleanup();
		exit(0);
	}

	//Create the socket
	SOCKET sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock == INVALID_SOCKET) {
		printf("Invalid Socket");
		printf("Error can't create socket");
		freeaddrinfo(res);
		WSACleanup();
		exit(0);

	}

	//Conect the Socket			
	int conresult = connect(sock, res->ai_addr, (int)res->ai_addrlen);
	if (conresult == SOCKET_ERROR) {
		printf("%d", conresult);
		printf("ERROR can't connect");
		closesocket(sock);
		freeaddrinfo(res);
		WSACleanup();
		exit(0);
	}
	freeaddrinfo(res); //
	return sock;
}


int SendToTwitch(SOCKET sock, char * str) {
	return send(sock, str, strnlen_s(str, 100), 0);
}


int ReceiveFromTwitch(SOCKET sock, char buf[]) {
	return recv(sock, buf, RECV_BUFFER, 0);
}