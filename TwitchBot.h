#pragma once
#include "Authenticate.h"
#include "Commands.h"
#include "Parser.h"
#include "SocketFunctions.h"
#include "TwitchbotMacros.h"
//https://en.wikipedia.org/wiki/List_of_Microsoft_Windows_versions       
#ifndef _WIN32_WINNT                                                           
#define _WIN32_WINNT 0x0600                                                    
#endif                                                                         
#if (_WIN32_WINNT < 0x0600) || !defined(_WIN32_WINNT)                          
#error Your windows version is too old                                         
#endif


typedef struct TwitchPRIVMSG {
	char badgeinfo[100];
	char badges[100];
	char bits[100];
	char channelname[100];
	char color[100];
	char displayname[100];
	char emotes[100];
	char flags[100];
	char id[100];
	char mod[100];
	char roomid[100];
	char Message[100];
	char subscriber[100];
	char timestamp[100];
	char turbo[100];
	char usertype[100];

} TwitchPRIVMSG;

//Recieve Data and store it in Message Struct
typedef struct Message {
	char name[RECV_BUFFER];
	char Gibberish[RECV_BUFFER];
	char Message[RECV_BUFFER];
	int PongReply;

} Message;
