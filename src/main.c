// main.c
#include "../header/yshell.h"

#define MAX_BUF_LEN 100
#define MAX_TOK_LEN 10

void print_token(char *tokens[]);    /* debug */
void get_current_dir(char *usr_name, char *shell_dir);
void parse(char *input, char*tokens[]);      /* Parse module */

int main() {
	int should_run = 1;    /* flag to determine when to exit program*/
	char *args[MAX_BUF_LEN] = {NULL};    /* user input arguments */

	// get user name
	uid_t id = getuid();
	struct passwd *user = getpwuid(id);
	char *usr_name = user->pw_name;

	while(should_run) {
		char *shell_dir = (char *)malloc(sizeof(char)*MAX_BUF_LEN);
		get_current_dir(usr_name, shell_dir);
		printf("YShell:%s$ ", shell_dir);
		fflush(stdout);

		char *input = (char *)malloc(sizeof(char)*MAX_BUF_LEN);
		fgets(input, MAX_BUF_LEN, stdin);
		if (input[0] == '\n' || input[0] == ' ')
			goto blank_input;
		else if (strcmp(input, "exit\n") == 0)
			break;
		parse(input, args);
		print_token(args);

		blank_input: ;
		free(shell_dir);
		free(input);
		memset(args, 0, sizeof(char*) * (MAX_BUF_LEN));
	}

	return 0;
}

void print_token(char *tokens[]) {
	int i = 0;
	while(tokens[i] != NULL)  {
		printf("%s\n", tokens[i]);
		++i;
	}
}

void get_current_dir(char *usr_name, char *shell_dir) {
	/* get current dir. */
	char *usr_dir = (char *)malloc(sizeof(char)*MAX_BUF_LEN);
	getcwd(usr_dir, MAX_BUF_LEN);

	/* replace "home/" to "~/" */
	if (strstr(usr_dir, usr_name) != NULL) {
		strcpy(shell_dir, "~/");
		strcat(shell_dir, strstr(usr_dir, usr_name));
	}
	else
		strcpy(shell_dir, usr_dir);

	free(usr_dir);
}

void parse(char *input, char *tokens[]) {
	char *token = NULL;
	int i = 0;

	token = strtok(input, " \n");
	while(token != NULL) {
			tokens[i] = (char *)malloc(sizeof(MAX_TOK_LEN));
			strcpy(tokens[i], token);
			token = strtok(NULL, " \n");
			++i;
	}
}
