#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


#ifndef FILE_PATH
#define FILE_PATH	"./testfile.txt"
#endif

#define BUFF_SIZE	1024
#define ERROR(_errmesg_)	error(EXIT_FAILURE, errno, "%s:%d->%s\n",\
		 __FILE__, __LINE__, _errmesg_)

int main()
{
	int fd;
	int buff[BUFF_SIZE];

	/*fopen(FILE_PATH, "w+") */
	if ( -1 == (fd = open(FILE_PATH, O_CREAT | O_RDWR | O_TRUNC , 0644)))
		ERROR("open");

	if ( -1 == write(fd, "helloworld", 10))
		ERROR("write");
	lseek(fd, 1024, SEEK_SET);

#if 1
	if ( -1 == write(fd, "helloworld", 10))
		ERROR("write");

	if ( -1 == read(fd, buff, BUFF_SIZE))
		ERROR("read");
#endif
	close(fd);

	return 0;
}
