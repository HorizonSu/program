#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define error_exit(_errmsg_) 	error(EXIT_FAILURE, errno, _errmsg_)
#define BUF_SIZE 	1024
#define KEY_VALUE 	0x01020304

int seminit(int *semid, int value);
int semp(int semid);
int semv(int semid);
int semvalue(int semid);
int semdistr(int semid);

int main()
{
	int semid;
	int semval;
	
	seminit(&semid, 0);
	
	semval = semvalue(semid);
	printf("semval: %d\n", semval);
	
	semv(semid);
	
	semval = semvalue(semid);
	printf("semval: %d\n", semval);

	semp(semid);
	
#if 0
#endif

	semdistr(semid);

	return 0;
}

int seminit(int *semid, int value)
{
	int id;
	if (-1 == (id = semget(KEY_VALUE, 1, IPC_CREAT | 0666)))
		return -1;
	if (-1 == semctl(id, 0, SETVAL, value))
		return -1;
	*semid = id;
	return 0;
}

int semp(int semid)
{
	struct sembuf sopbuf;

	sopbuf.sem_num = 0;
	sopbuf.sem_op = -1;
	sopbuf.sem_flg = 0;

	if (-1 == semop(semid, &sopbuf, 1))
		return -1;
	return 0;
}

int semv(int semid)
{
	struct sembuf sopbuf;

	sopbuf.sem_num = 0;
	sopbuf.sem_op = 1;
	sopbuf.sem_flg = 0;

	if (-1 == semop(semid, &sopbuf, 1))
		return -1;
	return 0;
}

int semvalue(int semid)
{
	return semctl(semid, 0, GETVAL);
}

int semdistr(int semid)
{
	return semctl(semid, 0, IPC_RMID);
}
