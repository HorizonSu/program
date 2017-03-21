#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define BUFF_SIZE	1024

int main()
{
	pid_t pid;
	int pipefd[2];
	int counter = 0;
	FILE *fp;
	char buff[BUFF_SIZE];

	if (-1 == pipe(pipefd))
		error_exit("pipe");

	if (NULL == (fp = fdopen(pipefd[1], "w")))
		error_exit("fdopen");
	setbuf(fp, NULL);

	for (counter = 0; ; counter ++) {
		if (0 > fprintf(fp, "%0128d", counter))
			error_exit("fprintf");
		printf("%d\n", counter);
	}

	exit(EXIT_SUCCESS);
	return 0;
}
