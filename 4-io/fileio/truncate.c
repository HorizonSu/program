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
	int nbytes;

	if ( -1 == (fd = open(FILE_PATH, O_RDWR , 0644)))
		ERROR("open");

	lseek(fd, 1024, SEEK_SET);
	nbytes = read(fd, buff, BUFF_SIZE);
	
	lseek(fd, nbytes, SEEK_SET);
	write(fd, buff, nbytes);

	ftruncate(fd, nbytes << 1);

	
	close(fd);

	return 0;
}
