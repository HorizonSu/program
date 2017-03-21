#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define FIFO_PATH	"/tmp/testfifo"
#define BUFF_SIZE	1024

int main()
{
	int fifd;
	char buff[BUFF_SIZE];
	
	if (-1 == mkfifo(FIFO_PATH, 0666)) {
		if (EEXIST != errno)
			error_exit("mkfifo");
	}

	 if (-1 == (fifd = open(FIFO_PATH, O_WRONLY)))
		 error_exit("open");

	while (1) {
		puts(">");
		fgets(buff, BUFF_SIZE, stdin);
		if (-1 == write(fifd, buff, strlen(buff)+1))
			error_exit("write");
	}

	close(fifd);
	return 0;
}
