#include "Authenticate.h"
#include "Commands.h"
#include "Parser.h"
#include "SocketFunctions.h"
#include "TwitchBot.h"
#include "TwitchbotMacros.h"

//bad Authenticate but will fix later
int Authenticate(char * username) {
	if (strncmp(username, "******",strnlen_s(username, 100)) == 0) {
		printf("Authorized User\n");
		return 1;
	}
	printf("Unauthorized User\n");
	return 0;;

}