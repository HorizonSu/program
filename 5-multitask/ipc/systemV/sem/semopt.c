#include <sys/user.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)
#define IPC_KEY		0X01020304
#define KEY_FILE	"."
#define KEY_MAGIC	'A'

#define SEMNUMS		2

int main()
{
	int semid;
	int semval;
	unsigned short semarry[SEMNUMS];
	struct sembuf semops;
#if 0
	/* not necessary */
	union _semuin_  {
		int val;
		struct semid_ds *dsbuf;
		unsigned short *arrays;
		struct seminfo *infobuf;
	}semuin = {
		.val = 10,
	}
#endif

	/* create semaphore set */
	if (-1 == (semid = semget(IPC_KEY, SEMNUMS,IPC_CREAT | 0666)))
		error_exit("semget");

#if 0
	/* get single value before SETVAL */
	if (-1 == (semval = semctl(semid, 0, GETVAL)))
		error_exit("semctl.GETVAL");
	printf("semval[0]: %d\n", semval);

	/* set value */
	if (-1 == semctl(semid, 0, SETVAL, 10))
		error_exit("semctl.SETVAL");

	/* get value after SETVAL */
	if (-1 == (semval = semctl(semid, 0, GETVAL)))
		error_exit("semctl.GETVAL");
	printf("semval[0]: %d\n", semval);

#else
	/* get all values before SETVAL */
	if (-1 == (semval = semctl(semid, 0, GETALL, semarry)))
		error_exit("semctl.GETVAL");
	printf("semval[0]: %d\nsemval[1]: %d\n", semarry[0], semarry[1]);
	
	/* set all values */
	semarry[0] = 0; /* read operation disable*/
	semarry[1] = 1;	/* write operation enable */
	if (-1 == semctl(semid, 0, SETALL, semarry))
		error_exit("semctl.SETVAL");
	
	/* get all values before SETVAL */
	if (-1 == (semval = semctl(semid, 0, GETALL, semarry)))
		error_exit("semctl.GETVAL");
	printf("semval[0]: %d\nsemval[1]: %d\n", semarry[0], semarry[1]);

#endif

	puts("semops V read ...");

	/* read, V operation */
	semops.sem_num = 0;	/* semaphore read */
	semops.sem_op = 1;	/* V operation */
	semops.sem_flg = 0;	/* default, enable block */
	
	if (-1 == semop(semid, &semops, 1))
		error_exit("semop.P");

	puts(" after semops V read ...");

	/* read, P operation */
	semops.sem_num = 0;	/* semaphore read */
	semops.sem_op = -1;	/* P operation */
	semops.sem_flg = 0;	/* default, enable block */
	
	if (-1 == semop(semid, &semops, 1))
		error_exit("semop.P");

	puts("after P ...");

	/* remove semaphore set */
	if (-1 == semctl(semid, 0, IPC_RMID))
		error_exit("semctl.IPC_RMID");

	return 0;
}
