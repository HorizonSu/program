#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#if 0

int main()
{
	int pid;
	int pid2;

	pid = fork();
	if(pid > 0)
	{
		wait(NULL);
		printf("father: %d\n", getpid());
		getchar();
	}
	else
	{
		pid2 = fork();
		if(pid2 > 0)
		{
			printf("son: %d\n", getpid());
			exit(0);
		}
		else{
			printf("grandson: %d\n", getpid());
			exit(0);
		}
	}
}
#endif


#if 0
void fun(int signu);

int main()
{
	int pid;

	signal(SIGCHLD, fun);

	pid = fork();
	if(pid > 0)
	{
		getchar();

	}else
	{
		exit(0);
	}
}

void fun(int signu)
{
	puts("son die !");
	wait(NULL);
}
#endif

int main()
{
	int pid;

	signal(SIGCHLD, SIG_IGN);

	pid = fork();

	if(pid > 0)
		getchar();
	else
		exit(0);
}
