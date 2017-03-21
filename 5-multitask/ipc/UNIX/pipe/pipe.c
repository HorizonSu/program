#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFF_SIZE	1024
#define ERROR(_errmsg_)		error(EXIT_FAILURE, errno, "%s:%d->%s\n", \
		__FILE__, __LINE__, _errmsg_)

int main(int argc, const char *argv[])
{
	int pfd[2];
	pid_t pid;
	FILE *fp = NULL;
	char buff[BUFF_SIZE];
	int flag;

	if (-1 == pipe(pfd))
		ERROR("pipe");
	
	pid = fork();
	if (pid == 0) {
		close(pfd[1]);
		flag = fcntl(pfd[0], F_GETFL);
		fcntl(pfd[0], F_SETFL, flag | O_NONBLOCK);
		if (NULL == (fp = fdopen(pfd[0], "r")))
			ERROR("fdopen");
		setvbuf(fp, buff, _IOLBF,  BUFF_SIZE);
		while (1) {
			fgets(buff, BUFF_SIZE, fp);
			fprintf(stdout, "child receive: %s\n", buff);
		}
	}else if (pid > 0) {
		close(pfd[0]);
		if (NULL == (fp = fdopen(pfd[1], "w")))
			ERROR("fdopen");
		setvbuf(fp, buff, _IOLBF,  BUFF_SIZE);
		while (1) {
			puts("enter your string:");
			fgets(buff, BUFF_SIZE, stdin);
			fprintf(fp, "%s", buff);
		}
	}else
		ERROR("fork");

	return 0;
}
