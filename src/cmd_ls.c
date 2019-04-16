// cmd_ls.c
#include "yshell.h"
#define MAX_BUF_LEN 200

extern void cmd_ls(char *tokens[]) {
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
	printf("\n");
	free(current_dir);
	closedir(dir);
}
