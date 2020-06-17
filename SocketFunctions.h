#pragma once
#include "Authenticate.h"
#include "Commands.h"
#include "Parser.h"
#include "TwitchBot.h"
#include "TwitchbotMacros.h"

SOCKET Initialize();
int SendToTwitch(SOCKET sock, char * str);
int ReceiveFromTwitch(SOCKET sock, char buf[]);
