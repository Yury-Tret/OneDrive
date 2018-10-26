#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "networking.h"

int run_syncing()
{
	int sockfd = connect_to_host("floatrates.com", 80);
	char message[1000];
	strcpy(message, "GET /daily/usd.json HTTP/1.1\r\nhost: floatrates.com\r\n\r\n");
	send_request(sockfd, message);
	char* reply = get_reply(sockfd);
	close(sockfd);
	printf("%s\n", reply);
	free(reply);
	return 0;
}
