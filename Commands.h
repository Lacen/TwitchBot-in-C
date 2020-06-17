#pragma once
#include "Authenticate.h"
#include "Parser.h"
#include "SocketFunctions.h"
#include "TwitchBot.h"
#include "TwitchbotMacros.h"


void Bracket(SOCKET  sock);
void Commands(SOCKET sock, Message msg);
void Eightball(SOCKET  sock);
int JoinRoom(SOCKET sock, char * Channel);
void Login(SOCKET sock);
void StringSender(SOCKET sock, char buf[]);