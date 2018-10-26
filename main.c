//#include <stdio.h>
#include <unistd.h>
#include "core.h"

int main(int argc, char **argv)
{
	int update_period = 300; //temp conf setting - pause between checking cloud
	
	while (1)
	{
		run_syncing();
		sleep(update_period);
	}
	return 0;
}
/*
#include <pthread.h>
void* threadFunc(void* argc)
{
   
    return 0;
}

int connect_to_cloud()
{
    pthread_t pth;
    pthread_create(&pth, NULL, threadFunc, NULL);
    pthread_join(pth, NULL);
    return 0;
}
*/