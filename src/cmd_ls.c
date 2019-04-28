// cmd_ls.c
#include "yshell.h"

void cmd_ls(int num_tokens, char *tokens[]) {
	char *current_dir = (char *)malloc(sizeof(char)*BUF_SIZE);
	DIR *dir = NULL;
	struct dirent *entry = NULL;
	char flg_show_all = 0;  /* flag to determine either show file starting with '.' */

	if(num_tokens > 2) {
		printf("ERROR@cmd_ls():too many args!\n");
		return;
	}
	if(tokens[0] != NULL) {
		if(!strcmp(tokens[0], "-a"))
			flg_show_all = 1;
		else {
			printf("ERROR@cmd_ls():wrong option!\n");
			return;
		}
	}
	getcwd(current_dir, BUF_SIZE);
	dir = opendir(current_dir);
	if(dir == NULL) {
		printf("ERROR@cmd_ls():opendir() failed!\n");
		return;
	}

	entry = readdir(dir);	
	while(entry != NULL) {  /* print directory entries */
		if(flg_show_all == 0 && entry->d_name[0] == '.') {
			entry = readdir(dir);
			continue;
		}
		switch(entry->d_type) {  /* set text color depanding on d_type */
			case 4:    /* directory file */
				printf("%c[1;34m", 27);
				break;
			case 2:    /* character device file */
				printf("%c[1;33m", 27);
				break;
			case 6:    /* block device file */
				printf("%c[1;33m", 27);
				break;
			case 10:    /* link file */
				printf("%c[1;36m", 27);
				break;
		}
		printf("%-s\t", entry->d_name);
		printf("%c[0m", 27);  /* set text color to default */
		entry = readdir(dir);
	}
	printf("\n");
	free(current_dir);
	closedir(dir);
}
