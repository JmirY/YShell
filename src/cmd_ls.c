// cmd_ls.c
#include "yshell.h"
#define MAX_BUF_LEN 200

void cmd_ls(char *tokens[]) {
	char *current_dir = (char *)malloc(sizeof(char)*MAX_BUF_LEN);
	DIR *dir = NULL;
	struct dirent *entry = NULL;
	char flg_show_all = 0;  /* flag to determine either show files start with '.' */

	if(tokens[0] != NULL) {
		if(!strcmp(tokens[0], "-a"))
			flg_show_all = 1;
		else {
			printf("ERROR@cmd_ls(): Wrong option!\n");
			return;
		}
	}
	getcwd(current_dir, MAX_BUF_LEN);
	dir = opendir(current_dir);
	if(dir == NULL) {
		printf("ERROR@cmd_ls()\n");
		return;
	}

	entry = readdir(dir);
	while(entry != NULL) {
		if(flg_show_all == 0 && entry->d_name[0] == '.') {
			entry = readdir(dir);
			continue;
		}
		printf("%s\t", entry->d_name);
		entry = readdir(dir);
	}
	printf("\n");
	free(current_dir);
	closedir(dir);
}
