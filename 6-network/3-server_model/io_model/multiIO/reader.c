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
	int fifd,
		maxfd;
	char buff[BUFF_SIZE];
	int flag;
	fd_set rdfds,
		   tmpfds;
	
	if (-1 == mkfifo(FIFO_PATH, 0666)) {
		if (EEXIST != errno)
			error_exit("mkfifo");
	}

	if (-1 == (fifd = open(FIFO_PATH, O_RDONLY)))
		error_exit("open");

	FD_ZERO(&rdfds);
	FD_SET(0, &rdfds);
	FD_SET(fifd, &rdfds);
	maxfd = fifd;
	tmpfds = rdfds;

#if 1
	while (1) {

		puts("before select ...... ");
		rdfds = tmpfds;
		if (-1 == select(maxfd + 1, &rdfds, NULL, NULL, NULL))
			error_exit("select");
		puts("wake up ...... ");

		if (FD_ISSET(0, &rdfds)) {
			if (NULL != fgets(buff, BUFF_SIZE, stdin))
				printf("stdin: %s", buff);
		}
		if (FD_ISSET(fifd, &rdfds)) {
			if (0 < read(fifd, buff, BUFF_SIZE))
				printf("fifo: %s", buff);
		}
	}

	close(fifd);
#endif
	return 0;
}
