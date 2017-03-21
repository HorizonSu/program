#include "head.h"

int main(void)
{
	mesg_t *mesgbuff;
	int shmid;
	void *shmaddr = NULL;

	int semid;
	short semvals[2];
	struct sembuf semopt;

	/*******    create of open  shared memory   ********/
	if (-1 == (shmid = shmget(KEY_VALUE, MEM_SIZE, IPC_CREAT | 0666)))
		ERROR("shmget");

	/*******      attach memory      *******/
	if ( (void *)-1 == (shmaddr = shmat(shmid, NULL, SHM_RND)))
		ERROR("shmat");

	/*****    create or open semaphore arrays   ********/
	if (-1 == (semid = semget(KEY_VALUE, 2, IPC_CREAT | IPC_EXCL | 0666))) {
		if (EEXIST == errno) {
			if (-1 == (semid = semget(KEY_VALUE, 0, 0666)))
				ERROR("semget.open");
		}else
			ERROR("semget.create");
	}else {
		/****     initialize semaphore arrays   ***/
		semvals[0] = 0;		/*  read operation disable  */
		semvals[1] = 1;		/*  write operation enable  */
		if (-1 == semctl(semid, 0, SETALL, semvals))
			ERROR("semctl.getval");
	}
	
	/*****     initialize memory values    ******/
	mesgbuff = shmaddr;
	mesgbuff->pidw = getpid();

	/*****  main loop   ****/
	while (1) {
		/*******  P operation for write  ******/
//		puts("waiting for P write ...");
		semopt.sem_num = 1;
		semopt.sem_op = -1;
		semopt.sem_flg = 0;
		if (-1 == semop(semid, &semopt, 1))
			ERROR("semop.P write");

		/************  get user data   ***********/
		printf(">>");
		fflush(stdout);
		fgets(mesgbuff->buff, BUFF_SIZE, stdin);

		/*******  V operation for read  ******/
//		puts("waiting for V read ... ");
		semopt.sem_num = 0;
		semopt.sem_op = 1;
		semopt.sem_flg = 0;
		if (-1 == semop(semid, &semopt, 1))
			ERROR("semop.V read");
		
		if (!strcmp("#quit\n", mesgbuff->buff))
			goto Quit;
	}

Quit:
	sleep(1);	/* waiting for reader exit */
	if (-1 == semctl(semid, 0, IPC_RMID))
		ERROR("semctl.IPC_RMID");
	if (-1 == shmdt(shmaddr))
		ERROR("shmdt");
	if (-1 == shmctl(shmid, IPC_RMID, NULL))
		ERROR("shmctl.IPC_RMID");
	exit(EXIT_SUCCESS);	
}
