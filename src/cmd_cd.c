// cmd_cd.c
#include "yshell.h"

extern char *usr_name;

void cmd_cd(int num_tokens, char *tokens[]) {
	char *dest = (char *)malloc(sizeof(char)*BUF_SIZE);    /* destination dir. */
	char *cur = (char *)malloc(sizeof(char)*BUF_SIZE);  /* current dir. */
	memset(dest, 0, sizeof(char)*BUF_SIZE);
	getcwd(cur, BUF_SIZE);

	if(num_tokens > 2) {
		printf("ERROR@cmd_cd():too many args!\n");
		return;
	}
	if(tokens[0] == NULL) { /* cd */
		strcat(dest, "/home/");
		strcat(dest, usr_name);
	}
	else if( strcmp(tokens[0], ".") == 0 ) { /* cd . */
		strcpy(dest, cur);	
	}
	else if( strcmp(tokens[0], "..") == 0 ) { /* cd .. */
		if( cur == strrchr(cur, '/') )  /* parent dir. is root dir. */
			strcpy(dest, "/");
		else {
			char *ptr = strrchr(cur, '/');
			*ptr = '\0';
			strcpy(dest, cur);	
		}
	}
	else if( tokens[0] == strchr(tokens[0], '/') )  /* absolute path */
		strcpy(dest, tokens[0]);
	else {
		strcat(dest, cur);
		strcat(dest, "/");
		strcat(dest, tokens[0]);
	}

	if(chdir(dest) == -1)
		printf("ERROR@chdir():chdir() failed!\n");

	free(dest);
	free(cur);
}
