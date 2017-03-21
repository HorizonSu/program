#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define BUFF_SIZE	1024

int main()
{
	pid_t pid;
	int pipefd[2];
	char buff[BUFF_SIZE];

	if (-1 == pipe(pipefd))
		ERROR_EXIT("pipe");

	pid = fork();
	if (0 == pid) { /* child */	
		close(pipefd[0]);
#if 0
		buff[0] = 0;
		if (0 >= read(pipefd[0], buff, BUFF_SIZE))
			ERROR_EXIT("read");
		printf("read: %s\n", buff);
#endif
	}else if (0 < pid) {	/* father */
		close(pipefd[0];
//		signal(SIGPIPE, SIG_IGN);
		sleep(1);
		strcpy(buff, "helloworld");
		if (0 >= write(pipefd[1], buff, strlen(buff)))
			ERROR_EXIT("write");
		printf("write: %s\n", buff);
	}

	exit(EXIT_SUCCESS);
	return 0;
}
