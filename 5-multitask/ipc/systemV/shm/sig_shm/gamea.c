#include "head.h"

void signal_handler(int signo);
mesg_st *buff;
int shmid;

int main()
{
	
	if (-1 == (shmid = shmget(KEY_VALUE, MEM_SIZE, IPC_CREAT | 0666)))
		ERROR_EXIT("shmget");
	if ((void *)-1 == (buff = shmat(shmid, NULL, 0)))
		ERROR_EXIT("shmat");

	signal(SIGUSR1, signal_handler);

	buff->pida = getpid();
	buff->value = 100;

	while(1)
		sleep(1);

	return 0;
}

void signal_handler(int signo)
{
	printf("gamea:%d\n", buff->value);
	buff->value --;
	if (0 == buff->value) {
		kill(buff->pidb, SIGKILL);
		shmdt(buff);
		shmctl(shmid, IPC_RMID, NULL);
		exit(EXIT_SUCCESS);
	}
	kill(buff->pidb, SIGUSR1);
}

