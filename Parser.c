#include "Authenticate.h"
#include "Commands.h"
#include "Parser.h"
#include "SocketFunctions.h"
#include "TwitchBot.h"
#include "TwitchbotMacros.h"
//Parser
void Parser(char buf[], Message *Mess) {
	//We clear all the data inside of the Message struct and make it ready for data to be filled.
	memset(Mess->name, '\0', RECV_BUFFER);
	memset(Mess->Gibberish, '\0', RECV_BUFFER);
	memset(Mess->Message, '\0', RECV_BUFFER);
	Mess->PongReply = 0;
	//strtok variables
	char * token = NULL;
	char * pos = NULL;
	char delim[] = "!:";

	//Checking if it is a server Reply and setting it to true if it is else we know is a Command and we can parse and store data in the Message Struct
	if (buf[0] == 'P') {
		if (strstr(buf, "PING :tmi.twitch.tv") != NULL) {
			Mess->PongReply = 1;
			return;
		}
	}
	else if (buf[0] == ':') {
		token = strtok_s(buf, delim, &pos);
		strncpy_s(Mess->name, RECV_BUFFER, token, 100);
		token = strtok_s(NULL, delim, &pos);
		strncpy_s(Mess->Gibberish, RECV_BUFFER, token, 100);
		token = strtok_s(NULL, "", &pos);
		strncpy_s(Mess->Message, RECV_BUFFER, token, 100);
		return;
	}

}

