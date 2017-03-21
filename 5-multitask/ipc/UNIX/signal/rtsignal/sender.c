#include <head.h>

int counter;

int main(int argc, const char **argv)
{
	for (counter = 0; counter < 10000; counter ++) {
		printf("SEND --------- %d\n", counter );
		if (-1 == kill(atoi(argv[1]), SIGRTMIN+20))
			error_exit("kill");
//		usleep(20000);
	}
}
