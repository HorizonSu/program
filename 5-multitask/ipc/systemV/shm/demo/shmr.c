#include <stdio.h>
#include <sys/user.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define KEY_VALUE	0X01020304

int main()
{
	int shmid;
	char *buff = NULL;
	int index;
	
	if (-1 == (shmid = shmget(KEY_VALUE, PAGE_SIZE, IPC_CREAT | 0666)))
		ERROR_EXIT("shmget");

	if ((void *)-1 == (buff = shmat(shmid, NULL, 0)))
		ERROR_EXIT("shmat");

//	strcpy(buff, "hello, world");

	if (-1 == shmdt(buff))
		ERROR_EXIT("shmdt");

	return 0;
}
