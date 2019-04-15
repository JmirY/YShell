/* yshell.h */
// C standard lib.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>

#define MAX_NAME_LEN 10

struct cmd_entry {
	char cmd_name[MAX_NAME_LEN];
	void (*cmd_fp)();
}

void cmd_ls();
