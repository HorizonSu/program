#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	printf("argv[0]: %s\n", argv[0]);
	printf("argv[1]: %s\n", argv[1]);
	printf("exe:VALUE:%s\n", getenv("VALUE"));
	printf("exe:PATH:%s\n", getenv("PATH"));
	printf("exe:HOME:%s\n", getenv("HOME"));

	return 0;
}
