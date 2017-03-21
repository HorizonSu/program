#include <stdio.h>
#include <head.h>

int main()
{
	int fd;
	struct flock flock;
	
	if (-1 == (fd = open("./lock_file", O_CREAT | O_RDWR, 0666)))
		error_exit("open");
	
	/* set write lock */
	flock.l_type = F_WRLCK;
	flock.l_whence = SEEK_SET;
	flock.l_start = 0;
	flock.l_len = 1024;	
	if (-1 == fcntl(fd, F_SETLKW, &flock))
		error_exit("fcntl");

	puts("set wlock ok ");

	getchar();
	
	/* set unlock */
	flock.l_type = F_UNLCK;
	flock.l_whence = SEEK_SET;
	flock.l_start = 0;
	flock.l_len = 1024;	
	if (-1 == fcntl(fd, F_SETLKW, &flock))
		error_exit("fcntl");

	puts("end");
}
