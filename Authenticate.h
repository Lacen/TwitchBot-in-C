#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "TwitchbotMacros.h"
#pragma comment (lib, "ws2_32.lib")
int Authenticate(char * username);

