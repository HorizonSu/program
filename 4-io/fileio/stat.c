#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return -1;

	struct stat statbuff;
	int mode;
	
	stat(argv[1], &statbuff);
	printf("nlink: %d\n", statbuff.st_nlink);
	printf("uid: %d\n", statbuff.st_uid);
	printf("size: %d\n", statbuff.st_size);

	printf("mode: %#o\n", statbuff.st_mode);
	mode = statbuff.st_mode;
	
	if ((mode & S_IRUSR) )
		puts("ur");
	if (mode & S_IWUSR)
		puts("uw");
	if (mode & S_IXUSR)
		puts("ux");


	if (S_ISREG(statbuff.st_mode))
		puts("regular");
	else if (S_ISBLK(statbuff.st_mode))
		puts("block");



	return 0;
}
