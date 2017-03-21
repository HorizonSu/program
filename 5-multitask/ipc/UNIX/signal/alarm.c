#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <error.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

int main()
{
//	signal(SIGALRM, SIG_IGN);
	puts("---------------");
	alarm(2);
	pause();

	puts("000000000000000");

	while(1);

	return 0;
}
