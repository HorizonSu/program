#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

#define BUFF_SIZE	256
#define ERROR(_errormesg_)	error(EXIT_FAILURE, errno, "%s:%d->%s\n", \
		__FILE__, __LINE__, _errormesg_)

int main(int argc, char **argv)
{
	DIR *dirp = NULL;
	char *filepath = NULL;
	struct dirent *entry = NULL;
	int fd;
	char buff[BUFF_SIZE];

	if (1 == argc)
		filepath = ".";
	else if (2 == argc)
		filepath = argv[1];
	else 
		ERROR("invalid argment");

#if 0
	if (NULL == (dirp = opendir(filepath)))
		ERROR("opendir");
#else
	if (-1 == (fd = open(filepath, O_DIRECTORY)))
		ERROR("open");
	if (NULL == (dirp = fdopendir(fd)))
		ERROR("fdopendir");
#endif

	while (NULL != (entry = readdir(dirp))) {
		printf("%-10ld %s\n", entry->d_ino, entry->d_name);
	}
	puts("----------------");
#if 0
	getcwd(buff, BUFF_SIZE);
	puts(buff);

	chdir("/home/james");
	getcwd(buff, BUFF_SIZE);
	puts(buff);
#endif

	seekdir(dirp, 0);

	mkdir("test", 0555);
	while (NULL != (entry = readdir(dirp))) {
		printf("%-10ld %s\n", entry->d_ino, entry->d_name);
	}
	chdir("test");
	creat("123", 0644);

#if 0
	chdir("..");
	unlink("test/123");
	rmdir("test");
#endif
	closedir(dirp);

	return 0;
}
