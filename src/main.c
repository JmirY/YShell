#include "header.h"

#define MAX_BUF_LEN 100

void get_current_dir(char *usr_name, char *shell_dir) {
	/* get current dir. */
	char *usr_dir = (char *)malloc(sizeof(char)*MAX_BUF_LEN);
	getcwd(usr_dir, MAX_BUF_LEN);

	/* cut off "home/" */
	strcpy(shell_dir, strstr(usr_dir, usr_name));

	free(usr_dir);
}

int main() {
	int should_run = 1;    /* flag to determine when to exit program*/

	// get user name
	uid_t id = getuid();
	struct passwd *user = getpwuid(id);
	char *usr_name = user->pw_name;

	while(should_run) {
		char *shell_dir = (char *)malloc(sizeof(char)*MAX_BUF_LEN);
		get_current_dir(usr_name, shell_dir);
		printf("YShell::%s$ ", shell_dir);
		fflush(stdout);

		free(shell_dir);
	}

	return 0;
}