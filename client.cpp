#include "client.h"

client::client(const char* givenhp) {
	std::cout << "client initialized" << std::endl;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0) {
		perror("Socket Failed...");
	}
			
	server.sin_family = AF_INET;
	
	hp = gethostbyname(givenhp);
	if(hp == 0) {
		perror("gethostbyname failed...");
		close(sock);
	}
	
	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	server.sin_port = htons(5000);
	
	if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0 ) {
		perror("Connect failed...");
		perror("The Server may not be up and running at the moment...");	
		perror("Check again later...");
		close(sock);
	}
	
	memset(buff, 0, sizeof(buff));
	if((rval = recv(sock, buff, sizeof(buff), 0)) < 0 ) {
		perror("Reading stream message error...");
	} else if(rval == 0) {
		printf("Ending connection\n");
	} else {
		printf("MSG: %s\n", buff);
	}
	printf("Got the message (rval=%d)\n", rval);
}

client::~client() {
	close(sock);
}

void client::sendInfo(const char* text) {
	std::cout << "sendinfo declared" << std::endl;
	if(send(sock, text, strlen(text), 0) < 0) {
		perror("Send failed...");
	} else {
		printf("Sent %s\n", text);
	}
	std::cout << "sendinfo finished" << std::endl;
}
