#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>

#define BUFF_SIZE	1024

typedef struct _globalmem_ {
	char mem[BUFF_SIZE];
	int memsize;
	sem_t sem_r,
		  sem_w;
}globalmem_st;

globalmem_st globalmem = {
	.memsize = BUFF_SIZE,
};

void * pthread_reader(void *arg);
void * pthread_writer(void *arg);

int main()
{
#if 0
	void *(*thread_handler[])(void *) = {
		pthread_reader,
		pthread_writer,
	};
#else
	void *thread_handler[] = {
		pthread_reader,
		pthread_writer,
	};
#endif
	const int THDNO = sizeof(thread_handler) / sizeof(*thread_handler);
	pthread_t tids[THDNO];
	int index;

	if ( -1 == sem_init(&globalmem.sem_r, 0, 0))
		perror("sem_init.sem_r");
	if (-1 == sem_init(&globalmem.sem_w, 0, 1))
		perror("sem_init.sem_w");

	for (index = 0; index < THDNO; index ++) {
		pthread_create(tids+index, NULL, thread_handler[index], NULL);
	}

	for (index = 0; index < THDNO; index ++)
		pthread_join(tids[index], NULL);
	
	return 0;
}

void * pthread_reader(void *arg)
{
	while (1) {
		sem_wait(&globalmem.sem_r);		//p
		puts("reader:");
		puts(globalmem.mem);
		sem_post(&globalmem.sem_w);		//v
	}
}

void * pthread_writer(void *arg)
{
	int counter = 0;
	
	while (1) {
		sem_wait(&globalmem.sem_w);		//p
		sprintf(globalmem.mem, "writer ---------- %d", counter ++);
		strcat(globalmem.mem, " *********");
		sem_post(&globalmem.sem_r);		//v
	}
}
