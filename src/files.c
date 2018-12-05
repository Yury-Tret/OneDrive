#include <stdio.h>


void *read_file(char *path, char *mode)
{
	FILE *fp = fopen(path, mode);
	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);
	rewind(fp);
	void *data = calloc(file_size, 1);
	fread(data, 1, file_size, fp);
	fclose(fp);
	return data;
}

void write_file(char *path, char *mode, void *data, size_t data_size)
{
	FILE *fp = fopen(path, mode);
	fwrite(data, 1, data_size, fp);
	fclose(fp);
}
