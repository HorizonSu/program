#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>

#ifndef FILE_PATH
#define FILE_PATH	"./testfile.txt"
#endif

#define BUFF_SIZE	1024
#define ERROR(_errmesg_)	error(EXIT_FAILURE, errno, "%s:%d->%s\n",\
		 __FILE__, __LINE__, _errmesg_)

int main()
{

#if 0
	int fd;

	if ( -1 == (fd = open(FILE_PATH, O_WRONLY)))
		ERROR("open");

	if ( -1 == write(fd, "helloworld", 10))
		ERROR("write");

	sleep(10);
	close(fd);

#endif

	FILE *fp = NULL;


	if (NULL == (fp = fopen(FILE_PATH, "w")))
		ERROR("fopen");
	if (0 == fwrite("helloworld", 1, 10, fp))
		ERROR("fwrite");
	fflush(fp);

	sleep(10);

	return 0;
}
