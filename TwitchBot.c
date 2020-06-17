#include "Authenticate.h"
#include "Commands.h"
#include "SocketFunctions.h"
#include "TwitchBot.h"
#include "TwitchbotMacros.h"
int main() {
	//Initalize Socket
	SOCKET sock = Initialize();
	//Login
	Login(sock);

	int exitstatus = 0;
	int RecvResult = 0;
	int SentResult = 0;
	int t;
	char buf[RECV_BUFFER];
	Message cmd;	//Check if the data recieve is a command or not


	//Main Loop
	do {
		
		memset(buf,'\0', RECV_BUFFER);
		RecvResult = recv(sock, buf, RECV_BUFFER, 0);

		//Debug display of data
		if (RecvResult > 0) {
			fflush(stdout);
			printf("%s\n", "MainLoop");
			printf("%s\n", buf);	
		}

		
		if (RecvResult > 0) {
			Parser(buf,&cmd);

			// This check if we are responding to twitch ping
			if (cmd.PongReply == 1) {
				SentResult = send(sock, "PONG :tmi.twitch.tv\r\n", strnlen_s("PONG :tmi.twitch.tv\r\n", 50), 0);
				printf("REPLYED TO PING REQUEST FROM TWITCH\n");
			}
			else if(cmd.Message[0] =='!'){

				printf("Message Recieved From: %s\n Gibberish: %s\n Message: %s\n", cmd.name, cmd.Gibberish, cmd.Message);
				//I probably should add some sort of authentication or privillage implementation later
					Commands(sock, cmd);

			}
		}
	
	} while (exitstatus == 0);
	
	
	//Exit Termination Cleanup
	//fclose(fp);
	closesocket(sock);
	WSACleanup();
	exit(0);

}

