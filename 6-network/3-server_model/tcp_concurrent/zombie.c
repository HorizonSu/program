#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void childhandler(int sig)
{
	puts("----------");
	wait(NULL);
}

int main()
{
	pid_t pid, pid2;

#if 0
	pid = fork();
	if (pid == 0) {
		pid2 = fork();
		if (pid > 0)
			exit(0);
		else {
			puts("gradeson:");
			sleep(3);
			exit(0);
		}
	} else {
		puts("father:");
		wait(NULL);
		getchar();
	}
#endif

//	signal(SIGCHLD, childhandler);
	signal(SIGCHLD, SIG_IGN);
	pid = fork();
	if (pid == 0)
		exit(0);
	else {
		puts("father");
	
		while (1 ) {
			waitpid(, WNOHANG);
			getchar();
		}
	}

	return 0;
}
