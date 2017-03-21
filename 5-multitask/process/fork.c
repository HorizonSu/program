#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>

int main()
{
	pid_t pid;

	if (0 > (pid = fork())) 
		error(EXIT_FAILURE, errno, "fail to fork --->%s:%s:%d\n",
				__FILE__, __func__, __LINE__);
	
	/* father process */
	if (pid > 0) {
		while (1) {
			printf("PPID[%d]------PID[%d]\n\tI`m father !\n",
					getppid(), getpid());
			sleep(1);
		}
	/* child process */
	} else {
		while (1) {
			printf("PPID[%d]------PID[%d]\n\tI`m child !\n",
					getppid(), getpid());
			sleep(1);
		}
	}

	return 0;
}
