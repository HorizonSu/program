/* for compare process and thread */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int globalvalue = 10;

int main()
{
	pid_t pid;

	pid = fork();
	if (0 == pid) {
		sleep(1);
		printf("globalvalue: %d\n", globalvalue);
	}else if (pid > 0) {
		globalvalue = 100000;
		exit(0);
	}

	exit(0);

}
