#include "head.h"

int main()
{
	int shmid;
	sem_t *sem_r = NULL,
		  *sem_w = NULL;
	mesg_st *msgbuf = NULL;
	time_t time_sec;
	struct tm * timbuf = NULL;

	if (SEM_FAILED == (sem_r = sem_open(SEM_READ, O_CREAT, 0666, 0)))
		error_exit("sem_open");
	if (SEM_FAILED == (sem_w = sem_open(SEM_WRITE, O_CREAT, 0666, 1)))
		error_exit("sem_open");
	
	if (-1 == (shmid = shmget(KEY_VALUE ,SHM_SIZE, IPC_CREAT | 0666)))
		error_exit("shmget");
	if ((void *)-1 == (msgbuf = shmat(shmid, NULL, 0)))
		error_exit("shmat");
	
	time(&time_sec);
	timbuf = localtime(&time_sec);
	
	msgbuf->pidw = getpid();
	msgbuf->value = timbuf->tm_sec;
	
	while (1) {
		sem_wait(sem_w);
		printf("write: %d\n", msgbuf->value --);
		if (msgbuf->value <= 0) { 
			kill(msgbuf->pidr, SIGKILL);
			break;
		}
		sem_post(sem_r);
	}

	sem_unlink(SEM_READ);
	sem_unlink(SEM_WRITE);
	return 0;
}
