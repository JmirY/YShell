// cmd_cd.c
#include "yshell.h"

#define MAX_BUF_LEN 100

extern char *usr_name;

void cmd_cd(char *tokens[]) {
	char *dest = (char *)malloc(sizeof(char)*MAX_BUF_LEN);    /* destination dir. */
	memset(dest, 0, sizeof(char)*MAX_BUF_LEN);
	char *cur = (char *)malloc(sizeof(char)*MAX_BUF_LEN);  /* current dir. */
	getcwd(cur, MAX_BUF_LEN);

	//printf("dest before cat: %s\n", dest);  /* debug */

	if(tokens[0] == NULL) {
		strcat(dest, "/home/");
		strcat(dest, usr_name);
	}
	else if( strcmp(tokens[0], ".") == 0 ) {
		strcpy(dest, cur);	
	}
	else if( strcmp(tokens[0], "..") == 0 ) {
		char *ptr = strrchr(cur, '/');
		*ptr = '\0';
		strcpy(dest, cur);	
	}
	else {
		strcat(dest, cur);
		strcat(dest, "/");
		strcat(dest, tokens[0]);
	}

	//printf("%s\n", dest);    /* debug */

	if(chdir(dest) == -1)
		printf("ERROR@chdir()\n");

	free(dest);
	free(cur);
}