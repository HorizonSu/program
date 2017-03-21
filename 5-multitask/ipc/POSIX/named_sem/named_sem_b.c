#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)
#define SEM_NAME_A	"james.a"
#define SEM_NAME_B	"james.b"

int main()
{
	sem_t *sem_a;
	sem_t *sem_b;
	int i;
	
	if (SEM_FAILED == (sem_a = sem_open(SEM_NAME_A, O_CREAT, 0666, 1)))
		perror("sem_open");
	if (SEM_FAILED == (sem_b = sem_open(SEM_NAME_B, O_CREAT, 0666, 0)))
		perror("sem_open");
	
	for (i = 0; i < 100; i ++) {
		sem_wait(sem_b);
		printf("A -------- %d\n", i);
		sem_post(sem_a);
	}

	if (-1 == sem_close(sem_a))
		error_exit("sem_close a");
	if (-1 == sem_close(sem_b))
		error_exit("sem_close b");

	sem_unlink(SEM_NAME_A);
	sem_unlink(SEM_NAME_B);

	return 0;
}
