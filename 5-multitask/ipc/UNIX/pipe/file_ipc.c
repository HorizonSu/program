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
	int fd;
	char buff[BUFF_SIZE];

	if (-1 == (fd = open("/tmp/ipc", O_CREAT | O_RDWR, 0777)))
		ERROR_EXIT("pipe");

	pid = fork();
	if (0 == pid) { /* child */	
		memset(buff, 0, BUFF_SIZE);
		if (0 >= read(fd, buff, BUFF_SIZE))
			ERROR_EXIT("read");
		printf("read: %s\n", buff);
	}else if (0 < pid) {	/* father */
		sleep(1);
		strcpy(buff, "helloworld");
		if (0 >= write(fd, buff, strlen(buff)))
			ERROR_EXIT("write");
		printf("write: %s\n", buff);
	}

	exit(EXIT_SUCCESS);
	return 0;
}
