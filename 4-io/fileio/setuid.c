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

	chmod("./a.out", 0755 | S_ISUID | S_ISGID);

	return 0;
}
