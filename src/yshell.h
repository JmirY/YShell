/* yshell.h */
// C standard lib.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>

#define MAX_NAME_LEN 10

typedef struct Cmd_entry {
	char cmd_name[MAX_NAME_LEN];
	void (*cmd_fp)();
} Cmd_entry;

void cmd_ls();
