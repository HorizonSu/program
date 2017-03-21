#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
#if 0
	char buff[128];
	int nbytes;

	nbytes = readlink("./lo", buff, 128);
	buff[nbytes] = '\0';
	puts(buff);
#endif
	if (argc != 3)
		exit(EXIT_FAILURE);
//	link(argv[1], argv[2]);
	symlink(argv[1], argv[2]);

	return 0;
}
