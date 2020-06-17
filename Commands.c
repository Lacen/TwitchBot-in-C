#include "Authenticate.h"
#include "Commands.h"
#include "Parser.h"
#include "SocketFunctions.h"
#include "TwitchBot.h"
#include "TwitchbotMacros.h"
char BracketString[RECV_BUFFER] = "There is no set bracket";

void Commands(SOCKET sock, Message msg) {

	//Strtok stuff and Argument handling
	char  ComBuffer[RECV_BUFFER];
	char  Arg[RECV_BUFFER];
	char * token;
	char * pos;
	//We need this because msg.Message does not have a null terminated string and we probably also want to ignore cases
	char Mess[RECV_BUFFER];
	memset(Mess, '\0', RECV_BUFFER);
	memset(ComBuffer, '\0', RECV_BUFFER);
	memset(Arg, '\0', RECV_BUFFER);
	strncpy_s(Mess, RECV_BUFFER, msg.Message, RECV_BUFFER);
	token = strtok_s(Mess, " ", &pos);
	strncpy_s(ComBuffer, RECV_BUFFER, token, 50);
	token = strtok_s(NULL, "", &pos);
	
	if (token != NULL) {
		strncpy_s(Arg, RECV_BUFFER, token, RECV_BUFFER);
	}
	//change it to all lowercase
	for (int i = 0; i < strnlen(ComBuffer, 50); i++) {
		ComBuffer[i] = tolower(ComBuffer[i]);
	}

	int SentResult = 0;
	
		//8Ball Command
		if (strncmp(ComBuffer, "!8ball", 6) == 0) {
			printf("Command Received is 8ball\n");
			Eightball(sock);

		}
		if (Authenticate(msg.name) == 1) {
			//Bracket Command
			if (strncmp(ComBuffer, "!bracket", 8) == 0) {
				printf("Command Received is Bracket\n");
				Bracket(sock);
			}
			//SetBracket Command
			if (strncmp(ComBuffer, "!setbracket", 11) == 0 && Arg[0] != '\0' && Authenticate(msg.name) == 1) {
				memset(BracketString, '\0', RECV_BUFFER);
				strncpy_s(BracketString, RECV_BUFFER, Arg, RECV_BUFFER);
				printf("Command Received is SetBracket\n");
				printf("This is the bracketString: %s\n", BracketString);
			}

			if (strncmp(ComBuffer, "!egor", 5) == 0) {
				StringSender(sock, "Egor is Bald");

			}

			if (strncmp(ComBuffer, "!protoss", 8) == 0) {
				StringSender(sock, "Protoss Good Race LUL");
			}

			if (strncmp(ComBuffer, "!terran", 7) == 0) {
				StringSender(sock, "MECH IMBA");
			}		
			if (strncmp(ComBuffer, "!gg", 3) == 0) {
				StringSender(sock, "GG EMINI");
			}
			
		}
	


}

//Bracket Function
void Bracket(SOCKET sock) {
	printf("Bytes sent from Bracket: ");
	StringSender(sock, BracketString);
}
//EightBall Function


void Eightball(SOCKET sock) {
	char Mess[RECV_BUFFER];
	char buf[RECV_BUFFER];
	memset(buf, '\0', RECV_BUFFER);
	memset(Mess, '\0', RECV_BUFFER);
	srand(time(0));
	int s = rand() % 20;
	switch (s) {
	case 0:
		strncpy_s(buf, RECV_BUFFER, "It is certain.", 15);
		break;
	case 1:
		strncpy_s(buf, RECV_BUFFER, "It is decidedly so.", 20);
		break;
	case 2:
		strncpy_s(buf, RECV_BUFFER, "Without a doubt.", 17);
		break;
	case 3:
		strncpy_s(buf, RECV_BUFFER, "Yes - definitely.", 18);
		break;
	case 4:
		strncpy_s(buf, RECV_BUFFER, "You may rely on it.", 20);
		break;
	case 5:
		strncpy_s(buf, RECV_BUFFER, "As I see it, yes.", 18);
		break;
	case 6:
		strncpy_s(buf, RECV_BUFFER, "Most likely.", 13);
		break;
	case 7:
		strncpy_s(buf, RECV_BUFFER, "Outlook good.", 14);
		break;
		strncpy_s(buf, RECV_BUFFER, "Yes.", 5);
		break;
	case 8:
		strncpy_s(buf, RECV_BUFFER, "Signs point to yes.", 20);
		break;
	case 9:
		strncpy_s(buf, RECV_BUFFER, " Reply hazy, try again.", 24);
		break;
	case 10:
		strncpy_s(buf, RECV_BUFFER, "Ask again later.", 17);
		break;
	case 11:
		strncpy_s(buf, RECV_BUFFER, "Better not tell you now.", 25);
		break;
	case 12:
		strncpy_s(buf, RECV_BUFFER, "Cannot predict now.", 20);
		break;

	case 13:
		strncpy_s(buf, RECV_BUFFER, "Concentrate and ask again", 26);
		break;
	case 14:
		strncpy_s(buf, RECV_BUFFER, "Don't count on it.", 19);
		break;
	case 15:
		strncpy_s(buf, RECV_BUFFER, "My reply is no.", 16);
		break;
	case 16:
		strncpy_s(buf, RECV_BUFFER, "Cannot predict now.", 20);
		break;
	case 17:
		strncpy_s(buf, RECV_BUFFER, "My sources say no.", 19);
		break;
	case 18:
		strncpy_s(buf, RECV_BUFFER, "Outlook not so good.", 21);
		break;
	case 19:
		strncpy_s(buf, RECV_BUFFER, "Very doubtful.", 15);
		break;
	default:
		strncpy_s(buf, RECV_BUFFER, "The Answer is 42", 17);
	}

	char * HeadMessage = "PRIVMSG #****** :";
	char * EndMessage = "\r\n";
	strncpy_s(Mess, RECV_BUFFER, HeadMessage, 23);
	strcat_s(Mess, RECV_BUFFER, buf);
	strcat_s(Mess, RECV_BUFFER, EndMessage);

	printf("Bytes sent from 8ball: ");
	StringSender(sock, buf);
	

}


// JoinRoom Function
int JoinRoom(SOCKET sock, char * Channel) {
	char str[200];
	memset(str, '\0', 200);
	for (int i = 0; i <= strnlen_s(Channel, 100); i++) {
		str[i] = tolower(str[i]);
	}
	strncpy_s(str, 100, "JOIN #", 100);
	strncat_s(str, 100, Default_Channel, 100);
	strncat_s(str, 100, " \r\n", 100);
	return SendToTwitch(sock, str);
}


//Login Function
void Login(SOCKET sock) {

	int LoginResult = 0;
	int RecvResult = 0;
	char buf[RECV_BUFFER];

	printf("Authenticating Access to Twitch IRC Server\n");

	memset(buf, '\0', RECV_BUFFER); // Clear buffer 
	LoginResult = SendToTwitch(sock, OAUTH);
	LoginResult = SendToTwitch(sock, Nickname);
	RecvResult = ReceiveFromTwitch(sock, buf);
	printf("%s", buf);

	LoginResult = JoinRoom(sock, Default_Channel);
	memset(buf, '\0', RECV_BUFFER);
	RecvResult = ReceiveFromTwitch(sock, buf);
	printf("%s\n", buf);

	RecvResult = ReceiveFromTwitch(sock, buf);
	printf("%s\n", buf);
	printf("Login Sucess\n");


/*
	Depreciated 1.0 Version
	memset(buf, '\0', RECV_BUFFER);
	LoginResult = SendToTwitch(sock, Membership);
	RecvResult = ReceiveFromTwitch(sock, buf);
	printf("%s\n", buf);

	memset(buf, '\0', RECV_BUFFER);
	LoginResult = SendToTwitch(sock, Tag);
	RecvResult = ReceiveFromTwitch(sock, buf);
	printf("%s\n", buf);
	
	memset(buf, '\0', RECV_BUFFER);
	LoginResult = SendToTwitch(sock, Command);
	RecvResult = ReceiveFromTwitch(sock, buf);
	printf("%s\n", buf);

	memset(buf, '\0', RECV_BUFFER);
	LoginResult = SendToTwitch(sock, ChatRoom);
	RecvResult = ReceiveFromTwitch(sock, buf);
	printf("%s\n", buf);
	memset(buf, '\0', RECV_BUFFER);

	printf("END OF LOGIN\n\n");
	*/

}



//StringSender Function
void StringSender(SOCKET sock, char buf[]) {
	int sentbytes = 0;
	char str[RECV_BUFFER];
	char Mess[RECV_BUFFER];
	memset(str, '\0', RECV_BUFFER);
	memset(Mess, '\0', RECV_BUFFER);
	strncpy_s(str, RECV_BUFFER, "PRIVMSG #", 200);
	strncat_s(str, RECV_BUFFER, Default_Channel, 200);
	strncat_s(str, RECV_BUFFER, " :", 200);
	strncat_s(str, RECV_BUFFER, buf, 200);
	strncat_s(str, RECV_BUFFER, "\r\n", 200);
	sentbytes = send(sock, str, strnlen_s(str, RECV_BUFFER), 0);
	printf("%d\n", sentbytes);

}
