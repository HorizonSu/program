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
	int flag;
	
	if (-1 == mkfifo(FIFO_PATH, 0666)) {
		if (EEXIST != errno)
			error_exit("mkfifo");
	}

	if (-1 == (fifd = open(FIFO_PATH, O_RDONLY)))
		error_exit("open");

	while (1) {

		if (NULL != fgets(buff, BUFF_SIZE, stdin))
			printf("stdin: %s", buff);

		if (0 < read(fifd, buff, BUFF_SIZE))
			printf("fifo: %s", buff);
	}

	close(fifd);
	return 0;
}
