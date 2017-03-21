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

#define FIFO_PATH	"/tmp/fifo"
#define BUFF_SIZE	1024

int main()
{
	int fd;
	
	if (-1 == mkfifo(FIFO_PATH, 0777)) {
		if (EEXIST != errno)
			ERROR_EXIT("mkfifo");
	}

	if (-1 == (fd = open(FIFO_PATH, O_WRONLY)))
		ERROR_EXIT("open");

	while (0 < write(fd, "helloworld", 11))
		puts("write"), sleep(1);
	ERROR_EXIT("write");
	
	close(fd);
	return 0;
}
