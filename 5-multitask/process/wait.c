#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

int globalvalue = 10;

int main()
{
	pid_t  pid;
	int ret;
	int status;

	if (0 > (pid = fork()))
		error_exit("fork");
	
	/* child  */
	if (pid == 0) {
		getchar();
		puts("--------- child -----------");
		exit(2);

	/* father process */
	} else {
		ret = wait(&status);
		printf("ret: %d\n", ret);
		printf("status: %d\n", WEXITSTATUS(status));
		if (WIFEXITED(status))
			puts("exit ");
		if (WIFSIGNALED(status))
			puts("killed");
		sleep(5);
	}

	return 0;
}


//fork wait waitpid exit _exit()
