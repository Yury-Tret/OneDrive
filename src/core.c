#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "networking.h"
#include "core.h"

int run_syncing()
{
//	char * host = "query.yahooapis.com";//"floatrates.com";
//	unsigned short port = 443;//80;
//	int sockfd = connect_to_host(host, port);
//
//	//char message[1000];
//	//strcpy(message, "GET /daily/usd.json HTTP/1.1\r\nhost: floatrates.com\r\n\r\n");
//
//	//char * message = "GET /daily/usd.json HTTP/1.1\r\nhost: floatrates.com\r\n\r\n";
//	char * message = "GET /v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22nome%2C%20ak%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys HTTP/1.1\r\nhost: query.yahooapis.com\r\n\r\n";
//	send_request(sockfd, message);
//	char* reply = get_reply(sockfd);
//	close(sockfd);
//	printf("REPLY IS\n%s\n", reply);
//	free(reply);
	
	RPL rpl;
	rpl.ptr = (char*)calloc(1, sizeof(char));
	rpl.bytes = 0;
	RPL * prpl = &rpl;
	//char * str;
	//curl_request(&rpl, "https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22nome%2C%20ak%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys");
	//curl_request(&rpl, "https://login.microsoftonline.com/common/oauth2/v2.0/authorize?client_id=eca8fefe-6030-491a-98c4-7c13ec9b9841&scope=files.readwrite%20offline_access&response_type=code&redirect_uri=https://login.live.com/oauth20_desktop.srf");
	//curl_post(&rpl, "https://login.microsoftonline.com/common/oauth2/v2.0/token", "client_id=eca8fefe-6030-491a-98c4-7c13ec9b9841&redirect_uri=https://login.live.com/oauth20_desktop.srf&code=M9899fce7-e02e-d4bb-7596-0d7330738c95&grant_type=authorization_code");
	//curl_post(&rpl, "https://login.microsoftonline.com/common/oauth2/v2.0/token", "client_id=eca8fefe-6030-491a-98c4-7c13ec9b9841&redirect_uri=https://login.live.com/oauth20_desktop.srf&refresh_token=MCfj9aIawWQj4VasJ77nlgyM7THb8BMHTYhcDPugsv0zgCipVGGJpgcoBfQOqciL9Hj9I5Ey*Ey7flbyeRIckvZgfbw!x4qhmPnQU*nbRDrqKSdeie*A8F6kaxgZm!3gcKHmuw2p0Pt7SXxDbpw2fOTOGevJSLnKijuVNerWZEM!!wr3qFBDYYEWctAMxGdzzeezYYXSoAI4ZLbUF3o0AQwbukjgLUbsuBj4Glh!KYKDUPbsvpHwUOPS6!Qq1KSDUV268rocv1qYuIDhFaQY5VmsPWe3fC*TaJ2aU0ATd2eEgZViIC1Wek662OtU8Ww5UuLGnU0Y3j3L3fILeTjadIRyOnxLeY*OnaFoRruIJLrf8&grant_type=refresh_token");
	curl_request(&rpl, "https://graph.microsoft.com/v1.0/me/drive/root/children", "Authorization: bearer EwBgA8l6BAAURSN/FHlDW5xN74t6GzbtsBBeBUYAAQs4VrhWj9w0M/jkxdoqV1zwmgbIPLDvgKaISqVqZKIeJ+tjX9mqiFRpojAT8h3VzMAb+i7s8DeIeVQQKNs26WqL2fIfJ8aOum9iW0B9t2RtmbER7LSmndbFqOY9akFtKw+5rMfBb+O8fEe0iuI3pB238ONW4tYkN4/hGL+/+dNjUgX8W2uwpQ6Ind1lkHq25tnHOaYiHkszZMKyyJFaKHlNmRgaWKXuw9w3I7rUCN52ojyntOE0at0RIcgFZZ0GWIkahv+/hvBWHxkNeZTqZI9egLggUSgs1+tzMKcPK7Ak/3GuSFwpl4KXkff1U4fJ80BH7SOyXlNosnrxHx1SXGcDZgAACPfYsJHN2U6dMAIZT55OmZ+Jjpj7qq1FO6FeFUxPbASxnzZBVNIZbA1dKNWPDY9cNWKpRfe81npWyipAE7XC0kieBMrCy2MhzflZlbnrTpdwv5aotyImN2uSjc/FqorkyP7m8HwOzgM/VoVl3sIG5UJbsdm1Pp5RtY5nRJ/RNyfeHLdspfGPUaynlA3vGnwnNCWRJVmgz0cgeZqa6XzDhkw0F7nX7fPukwLn6YpibMpHcqX/ZHqrUHsa9S0ASxgzPk72qyFKJs5TO0JKh2AYXM+jeAG67ctSi3XueBPrkvVnWSrtqInbp4Iq7Wm+vXjJ/vFr2fVE8COC3Yct0T+enDRENPdnx/aPk1/8u+RR7vqbGPJVkev8i930IQZzs45jkAcL3STnx5MNG9NKfLk+lTb5UQYluQOe2pM2N686JbtFktI/fL7pjx4QZhAq9Fl8/46nlP6w6sqZo+4esy2+HXTMIqf4uoqsNH+09/hDH59oNcPjq0loUGF8GmyZ3PdYUQu2VxvR8ChOBroSB02KW79K9Omw6A6Wxy8CkIP5AwaFGJVsF7eqsDIlx7MnuHdxQSqvaPUGCLhFuqK4IBTJ/0ygTH28+JAShxewEWJKFvwX9NssmQRl2vFWhmuI7HzzYSBV5e2zdT73Tu9vAndfIiZYDxH78S/9II8NgD+f0t6mcVyp4noAh6kqSxz2f5EobxW8g9tO+ON7PHtYCRpVJTSY41wwYgabCP0jkHtN8VY994lHOjp2BQBHG2sC");
	printf("REPLY IS\n%s\n", rpl.ptr);
	return 0;
}


//GET
//https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22nome%2C%20ak%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys

