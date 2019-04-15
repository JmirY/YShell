// command_ls.c
#include "commands.h"
#define MAX_BUF_LEN 200

void yshell_ls() {
	char *current_dir = (char *)malloc(sizeof(char)*MAX_BUF_LEN);
	DIR *dir = NULL;
	struct dirent *entry = NULL;

	getcwd(current_dir, MAX_BUF_LEN);
	dir = opendir(current_dir);
	if(dir == NULL) {
		printf("ERROR\n");
		return;
	}
	entry = readdir(dir);
	while(entry != NULL) {
		printf("%s\t", entry->d_name);
		entry = readdir(dir);
	}
	free(current_dir);
	closedir(dir);
}
