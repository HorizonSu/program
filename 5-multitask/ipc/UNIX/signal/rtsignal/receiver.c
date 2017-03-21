#include <head.h>

int counter;

void usr1_handler(int signo)
{
	printf("SIGUSR1 --------------- %d\n", counter ++);
}

int main()
{
	signal(SIGRTMIN+20, usr1_handler);
	while (1)
		sleep(1);
}
