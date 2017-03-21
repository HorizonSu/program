#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

int main()
{
	puts("main: I`ll execute the `ls` command ... ...");

#if 0
	if ( -1 == execlp("ls", "ls", "-l", "--color=auto",NULL))
		error(EXIT_FAILURE, errno, "%s:%s:%d--->exec failure:",
				__FILE__, __func__, __LINE__);
#endif
	
#if 0
	if ( -1 == execl("/bin/ls", "ls", "-l", "--color=auto",NULL))
		error(EXIT_FAILURE, errno, "%s:%s:%d--->exec failure:",
				__FILE__, __func__, __LINE__);
#endif

#if 0
	char *argv[] = {"ls", "-l", NULL};
	if ( -1 == execv("/bin/ls", argv))
		error(EXIT_FAILURE, errno, "%s:%s:%d--->exec failure:",
				__FILE__, __func__, __LINE__);
#endif

#if 1
	char *argv[] = {"ls", "-l", NULL};
	char *env[] = {"VALUE=100", NULL};
	
	printf("main:PATH:%s\n", getenv("PATH"));
	printf("main:HOME:%s\n", getenv("HOME"));
	
	if ( -1 == execve("./execve_test", argv, env))
		error(EXIT_FAILURE, errno, "%s:%s:%d--->exec failure:",
				__FILE__, __func__, __LINE__);
#endif
	puts("I`m back to main !!");

//	exit(EXIT_SUCCESS);
	return 0;
}
