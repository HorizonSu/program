#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
//	remove(argv[1]);
	unlink(argv[1]);
	return 0;
}
