#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <error.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

int main(int argc, char *argv[])
{
	int signo;
	pid_t pid;

#if 0
	if (argc != 3) {
		puts("invalid argument !");
		exit(EXIT_FAILURE);
	}

	signo = atoi(argv[1]+1);
	pid = atoi(argv[2]);

	kill(pid, signo);
#endif

	if ( -1 == (pid = fork()))
		ERROR_EXIT("fork");
	if (0 == pid) {
		while(1);
	}else {
		if ( -1 == (pid = fork()))
			ERROR_EXIT("fork");
		if (0 == pid) {
			while(1);
		}
		else {
			getchar();
			puts("kill all ");
			if (-1 == kill(0, 9))
				ERROR_EXIT("kill");
		}
	}

	return 0;
}
