#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/*
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
*/

int connect_to_host(char *host, unsigned short port)
{
    struct hostent *server;
    server = gethostbyname(host);
	int sockfd = 0;
    struct sockaddr_in serv_addr;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Error : Could not create socket \n");
		return 1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
	//serv_addr.sin_addr.s_addr = *((unsigned int*)server->h_addr);
	printf("Connecting...\n");
    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		return 1;
    }
	printf("Connected\n");
    return sockfd;
}

int send_request(int sockfd, char* request)
{
	printf("Sending...\n");
	if(send(sockfd, request, strlen(request), 0) < 0)
	{
		printf("Send failed\n");
		return 1;
	}
	printf("Send complete\n");
	return 0;
}

char* get_reply(int sockfd)
{
	printf("Reading...\n");
	int bytes = 0;
	char* server_reply = calloc(50000, sizeof(server_reply));
	memset(server_reply, '0', sizeof(server_reply));
	bytes = recv(sockfd, server_reply, 50000, MSG_WAITALL);
	if(bytes < 0)
	{
		printf("Read failed\n");
	}
	printf("Read complete\n");
	return server_reply;
}
