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
#include <curl/curl.h>
#include "core.h"

/*
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
*/

//typedef struct reply {
//		char * ptr;
//		size_t bytes;
//	}RPL;

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

size_t write_func(void *ptr, size_t size, size_t nmemb, RPL *rpl)
{
	rpl->ptr = (char*)realloc(rpl->ptr, nmemb);
	memcpy(rpl->ptr, ptr, nmemb);
	//*pptr = (char*)calloc(nmemb, sizeof(char));
	//memcpy(*pptr, ptr, nmemb);
	printf("Write_func\n");
	return nmemb;
}

int curl_request(RPL *rpl, char* request, char* header)
{
	CURL *curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if(curl)
	{
		//struct string s;
		//init_string(&s);
		struct curl_slist *chunk = NULL;
		chunk = curl_slist_append(chunk, header);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		curl_easy_setopt(curl, CURLOPT_URL, request);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, rpl);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
        {
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

		//printf("%s\n", s.ptr);
		//free(s.ptr);

		/* always cleanup */
		curl_easy_cleanup(curl);
    }
	printf("curl_func\n");
	return 0;
}

int curl_post(RPL *rpl, char* url, char* data)
{
	CURL *curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if(curl)
	{
		//struct string s;
		//init_string(&s);
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_func);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, rpl);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
        {
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

		//printf("%s\n", s.ptr);
		//free(s.ptr);

		/* always cleanup */
		curl_easy_cleanup(curl);
    }
	printf("curl_post\n");
	return 0;
}
