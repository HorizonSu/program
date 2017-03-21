#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/user.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)
#define KEY_VALUE	0X01020304

int main()
{
	int shmid;
	key_t key = KEY_VALUE;
	char *buff = NULL;

	if ( -1 == (shmid = shmget(key, PAGE_SIZE, IPC_CREAT | IPC_EXCL | 0777))) {
		if (EEXIST == errno) {
			if (-1 == (shmid = shmget(KEY_VALUE, PAGE_SIZE,  0)))
				ERROR_EXIT("shmget.open");
		}else
			ERROR_EXIT("shmget.create");
	}
	
	buff = (char *)shmat(shmid, NULL, 0);

	strcpy(buff, "hell0");
	puts(buff);
	printf("shmid: %d\n", shmid);
	printf("key: %#x\n", key);

	getchar();

	shmdt(buff);

	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}
