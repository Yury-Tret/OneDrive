//#include <stdio.h>
#include <unistd.h>
#include "core.h"
#include "files.h"
#include "parsers.h"

int main(int argc, char **argv)
{
//	int update_period = 300; //temp conf setting - pause between checking cloud
//	
//	while (1)
//	{
//		run_syncing();
//		sleep(update_period);
//	}

CMDLINE *cmd_params = parse_command_line(argc, argv);
CONFIG *config_params = parse_config_file(cmd_params->config_file_path);

printf("update_interval - %d\n", config_params->update_interval);
printf("get_access_token_uri - %s\n", config_params->get_access_token_uri);
printf("refresh_access_token_uri - %s\n", config_params->refresh_access_token_uri);

//printf("argc is - %d\n", argc);
//printf("argv is - %s\n", argv[0]);
//printf("argv is - %s\n", argv[1]);
//
//char *data = "Test data";
//char *path = "test_data.txt";
//
//write_file(path, "w", data, strlen(data));
//
//char *result = read_file(path, "r");
//
//printf("This is result - %s\n", result);
	
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