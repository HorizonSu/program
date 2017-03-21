#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

int main()
{
	pid_t pid;
	int fd;
	int flag;

	if (-1 == (fd = open("/tmp/testfile", O_CREAT | O_RDWR \
			//		| O_CLOEXEC
					, 0644)))
		error(EXIT_FAILURE, errno, "open");

	flag = fcntl(fd, F_GETFD);
//	if ( 0 > fcntl(fd, F_SETFD, flag | FD_CLOEXEC))
//		error(EXIT_FAILURE, errno, "fcntl");


	pid = fork();
	if (pid == 0)	{//father process
		if (0 > execl("./closexec_test", "test", NULL))
			error(EXIT_FAILURE, errno, "execl");

	}
	
	return 0;
}
