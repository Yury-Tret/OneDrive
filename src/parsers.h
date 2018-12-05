#define START_CMD_SYMBOL "--"
#define END_CMD_SYMBOL "="
#define NEXT_LINE_SYMBOL "\n"
#define WHITE_SPACE_SYMBOL " "

typedef struct {
	char *config_file_path;
} CMDLINE;

static char *get_substring_between_patterns(const char*, const char*, char*);

CMDLINE *parse_command_line(int, char**);

typedef struct {
	int update_interval;
	char *get_access_token_uri;
	char *refresh_access_token_uri;
} CONFIG;

static void fill_config_struct(CONFIG*, char*, char*);

CONFIG *parse_config_file(char *);