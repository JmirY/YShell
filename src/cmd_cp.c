// cmd_cp.c
#include "yshell.h"

void cmd_cp(int num_tokens, char *tokens[]) 
{
	if(num_tokens > 3) {
		printf("ERROR@cmd_cp():too many args!\n");
		return;
	}
	else if(num_tokens < 3) {
		printf("ERROR@cmd_cp():too few args!\n");
		return;
	}
	else {
		int fd_src = open(tokens[0], O_RDONLY);  /* fd of src file */
		if(fd_src < 0) {
			printf("ERROR@cmd_cp():wrong src path!\n");
			return;
		}

		struct stat sb;  /* stat buffer */
		if( fstat(fd_src, &sb) < 0 ) {
			printf("ERROR@cmd_cp():fstat() failed!\n");
			return;
		}

		int fd_dest = open(tokens[1], O_WRONLY | O_CREAT | O_TRUNC,
		sb.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));  /* fd of dest file*/
		if(fd_dest < 0) {
			printf("ERROR@cmd_cp():wrong dest path!\n");
			return;
		}

		char *buf = (char *)malloc(sizeof(char)*BUF_SIZE);
		while( read(fd_src, buf, BUF_SIZE) > 0 ) {
			if( write(fd_dest, buf, BUF_SIZE) < 0 ) {
				printf("ERROR@cmd_cp():write() failed!\n");
				return;
			}
		}
		free(buf);
	}
}
