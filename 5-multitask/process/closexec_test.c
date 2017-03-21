#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	if (0 >= write(3, "helloworld", 11))
		perror("write");

	return 0;
}
