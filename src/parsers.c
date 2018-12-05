#include "parsers.h"
#include "files.h"
#include <string.h>

static char *get_substring_between_patterns(const char *start_pattern, const char *end_pattern, char *source_str)
{
	char *start_ptr = strstr(source_str, start_pattern);
	char *end_ptr = strstr(source_str, end_pattern);
	start_ptr += strlen(start_pattern);
	char *result = calloc(end_ptr - start_ptr + 1, 1);
	memcpy(result, start_ptr, end_ptr - start_ptr);
	return result;
}

CMDLINE *parse_command_line(int argc, char **argv)
{
	CMDLINE *cmd_params = calloc(1, sizeof(CMDLINE));
	for (int i = 1; i < argc; i++ )
	{
		char *cmdline_param = get_substring_between_patterns(START_CMD_SYMBOL, END_CMD_SYMBOL, argv[i]);
		if (strcmp(cmdline_param, "config-file") == 0)
		{
			char *cmdline_param_value = strstr(argv[i], END_CMD_SYMBOL);
			cmdline_param_value += 1;
			cmd_params->config_file_path = calloc(strlen(cmdline_param_value), sizeof(char));
			memcpy(cmd_params->config_file_path, cmdline_param_value, strlen(cmdline_param_value));
		}
		free(cmdline_param);
	}
	return cmd_params;
}

static void fill_config_struct(CONFIG *config_params, char *key, char *value)
{
	if (strcmp(key, "update_interval") == 0)
	{
		config_params->update_interval = atoi(value);
	}
	else if (strcmp(key, "get_access_token_uri") == 0)
	{
		config_params->get_access_token_uri = calloc(strlen(value), sizeof(char));
		memcpy(config_params->get_access_token_uri, value, strlen(value));
	}
	else if (strcmp(key, "refresh_access_token_uri") == 0)
	{
		config_params->refresh_access_token_uri = calloc(strlen(value), sizeof(char));
		memcpy(config_params->refresh_access_token_uri, value, strlen(value));
	}
}

CONFIG *parse_config_file(char *config_file_path)
{
	CONFIG *config_params = calloc(1, sizeof(CONFIG));
	char *raw_config = (char*)read_file(config_file_path, "r");
	char *line, *splited_line, *key;
	int flag = 0;
	do 
	{
		line = strsep(&raw_config, NEXT_LINE_SYMBOL);
		if (line != NULL)
		{
			char *buff = strdup(line);
			do
			{
				splited_line = strsep(&buff, WHITE_SPACE_SYMBOL);
				if (flag == 0 && splited_line != NULL)
				{
					key = strdup(splited_line);
					flag = 1;
				}
				else if (flag == 1)
				{
					fill_config_struct(config_params, key, splited_line);
					flag = 0;
				}
				
			}while(splited_line != NULL);
		}
		
	}while(line != NULL);
	
	free(raw_config);

	return config_params;
}