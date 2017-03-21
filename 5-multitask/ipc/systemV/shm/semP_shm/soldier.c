#include "head.h"

int main()
{
	int shmid;
	sem_t *sem_r = NULL,
		  *sem_w = NULL;
	mesg_st *msgbuf = NULL;
	
	if (SEM_FAILED == (sem_r = sem_open(SEM_READ, 0)))
		error_exit("sem_open");
	if (SEM_FAILED == (sem_w = sem_open(SEM_WRITE, 0)))
		error_exit("sem_open");
	
	if (-1 == (shmid = shmget(KEY_VALUE ,SHM_SIZE, IPC_CREAT | 0666)))
		error_exit("shmget");
	if ((void *)-1 == (msgbuf = shmat(shmid, NULL, 0)))
		error_exit("shmat");
	
	msgbuf->pidr = getpid();

	while (1) {
		sem_wait(sem_r);
		printf("read: %d\n", msgbuf->value --);
		if (msgbuf->value <= 0) { 
			kill(msgbuf->pidw, SIGKILL);
			break;
		}
			
		sem_post(sem_w);
	}

	sem_unlink(SEM_READ);
	sem_unlink(SEM_WRITE);
	return 0;
}
