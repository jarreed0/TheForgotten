#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <SDL/SDL.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#ifndef CLIENT_H
#define CLIENT_H

class client {
	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buff[1024];
	int rval;
	public:
	client(const char* givenhp);
	~client();
	void sendInfo(const char* text);
};

#endif
