// main.c
#include "yshell.h"

#define MAX_BUF_LEN 100
#define MAX_TOK_LEN 10
#define DIY_CMD_NUM 3

void print_token(char *tokens[]);    /* debug */
void get_current_dir(char *usr_name, char *shell_dir);
int parse(char *input, char*tokens[]);      /* Parse module */
void init_cmd_arr(Cmd_entry cmd_arr[]);
void execute(int num_tokens, char *tokens[], Cmd_entry cmd_arr[]);    /* Executer module */

char *usr_name;    /* for external use */

int main() {
	int should_run = 1;    /* flag to determine when to exit program*/
	char *args[MAX_BUF_LEN] = {NULL};    /* user input arguments */
	int argc = 0;

	// get user name
	uid_t id = getuid();
	struct passwd *user = getpwuid(id);
	usr_name = user->pw_name;

	// create array of command-entry struct
	Cmd_entry cmd_arr[DIY_CMD_NUM] = {0};
	init_cmd_arr(cmd_arr);

	system("clear");
	while(should_run) {
		char *shell_dir = (char *)malloc(sizeof(char)*MAX_BUF_LEN);
		get_current_dir(usr_name, shell_dir);
		printf("%c[1;35m", 27);
		printf("YShell:");
		printf("%c[1;36m", 27);
		printf("%s$ ", shell_dir);
		printf("%c[0m", 27);
		fflush(stdout);

		char *input = (char *)malloc(sizeof(char)*MAX_BUF_LEN);
		fgets(input, MAX_BUF_LEN, stdin);
		if (input[0] == '\n' || input[0] == ' ')
			goto blank_input;
		else if (strcmp(input, "exit\n") == 0)
			break;
		argc = parse(input, args);
		execute(argc, args, cmd_arr);

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
		strcpy(shell_dir, "~");
		strcat(shell_dir, strstr(usr_dir, usr_name)+strlen(usr_name));
	}
	else
		strcpy(shell_dir, usr_dir);

	free(usr_dir);
}

int parse(char *input, char *tokens[]) {
	char *token = NULL;
	int i = 0;

	token = strtok(input, " \n");
	while(token != NULL) {
			tokens[i] = (char *)malloc(sizeof(MAX_TOK_LEN));
			strcpy(tokens[i], token);
			token = strtok(NULL, " \n");
			++i;
	}

	return i;
}

void init_cmd_arr(Cmd_entry cmd_arr[]) {
	Cmd_entry cmd_ls_entry = {.cmd_name = "ls", .cmd_fp = cmd_ls};
	Cmd_entry cmd_cd_entry = {.cmd_name = "cd", .cmd_fp = cmd_cd};
	Cmd_entry cmd_cp_entry = {.cmd_name = "cp", .cmd_fp = cmd_cp};

	cmd_arr[0] = cmd_ls_entry;
	cmd_arr[1] = cmd_cd_entry;
	cmd_arr[2] = cmd_cp_entry;
}

void execute(int num_tokens, char *tokens[], Cmd_entry cmd_arr[]) {
	int i = 0;
	for(i = 0; i < DIY_CMD_NUM; ++i) {
		if(strcmp(tokens[0], cmd_arr[i].cmd_name) == 0)
			cmd_arr[i].cmd_fp(num_tokens, tokens+1);
	}
}
