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
#define KEY_FPATH	"./shmr.c"
#define KEY_MAGIC	'M'
#define SHM_ADDR	((void*)0xb0000fff)

#define MEM_SIZE	PAGE_SIZE

int main()
{
	int shmid;
	key_t key;
	char *buff = NULL;

	key = ftok(KEY_FPATH, KEY_MAGIC);
	
	if (-1 == (shmid = shmget(key, MEM_SIZE, IPC_CREAT | 0666)))
		ERROR_EXIT("shmget");

	if ((void *)-1 == (buff = shmat(shmid, SHM_ADDR, SHM_RND | SHM_RDONLY)))
		ERROR_EXIT("shmat");

	printf("buff: %p\n", buff);
	printf("&shmid: %p\n", &shmid);

//	strcpy(buff, "hello, world ------------------");

	shmctl(shmid, IPC_RMID, NULL);
	
	return 0;
}
