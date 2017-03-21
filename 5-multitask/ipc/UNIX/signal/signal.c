#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <error.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

void( *signal( int, void(*)(int) ) )(int);

typedef int * int32_p;

typedef void(*sig_handler_t)(int);
sig_handler_t signal(int, sig_handler_t);



void signal_handler(int signo)
{
	switch (signo) {
		case SIGALRM:
			puts("SIGALRM");
			break;
		case SIGPIPE:
			puts("SIGPIPE");
			break;
		case SIGUSR1:
			puts("SIGPUSR1");
			break;
		case SIGUSR2:
			puts("SIGUSR2");
			break;
		case SIGSEGV:
			puts("SIGSEGV");
			break;
		case SIGKILL:
			puts("kill");
			break;
		default:
			puts("unkown signal !!");
			break;
	}
}

int main()
{	
#if 0
	/********** test signal_handler *****************/
	signal(SIGALRM, signal_handler);
	signal(SIGPIPE, signal_handler);
	signal(SIGSEGV, signal_handler);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGKILL, signal_handler);
	puts("---------- signal will not block -------");
#endif

#if 1
	/********* test SIG_DFL ***********/
	signal(SIGPIPE, signal_handler);
	getchar();
	signal(SIGPIPE, SIG_DFL);
#endif

#if 1
	/*************  test SIG_IGN  ***********/
	int pfids[2];
	signal(SIGPIPE, SIG_IGN);

	pipe(pfids);
	close(pfids[0]);

	write(pfids[1], "hello", 5);
#endif


	while(1);

	return 0;
}
