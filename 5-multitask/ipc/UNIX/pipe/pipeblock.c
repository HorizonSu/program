#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define BUFF_SIZE	1024
#define ERROR(_errmsg_)		error(EXIT_FAILURE, errno, "%s:%d->%s\n", \
		__FILE__, __LINE__, _errmsg_)

int pipesize;

int main(int argc, const char *argv[])
{
	int pfd[2];
	pid_t pid;
	FILE *fp = NULL;
	char buff[BUFF_SIZE];
	int flag;
	int ret;

	if (-1 == pipe(pfd))
		ERROR("pipe");
	

	
	pid = fork();
	if (pid == 0) {
		close(pfd[1]);
		while (1) {
			if ( 0 >= (ret = read(pfd[0], buff, BUFF_SIZE)))
				perror("read");
			printf("receive:[%d]%s\n", ret, buff);
			sleep(1);
		}
	}else if (pid > 0) {
		signal(SIGPIPE, SIG_IGN);
		close(pfd[0]);
		while (1) {
			if ( 0 >= write(pfd[1], "helloworld\n", 11))
				perror("write");
			printf("write: %d\n", pipesize ++);
		}
	}else
		ERROR("fork");

	return 0;
}
