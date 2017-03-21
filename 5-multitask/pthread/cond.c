#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

#define BUFF_SIZE	1024

typedef struct _globalmem_ {
	char mem[BUFF_SIZE];
	int memsize;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}globalmem_st;

globalmem_st globalmem = {
	.memsize = BUFF_SIZE,
	.mutex = PTHREAD_MUTEX_INITIALIZER,
	.cond = PTHREAD_COND_INITIALIZER,
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
		pthread_reader,
		pthread_reader,
		pthread_reader,
		pthread_writer,
	};
#endif
	const int THDNO = sizeof(thread_handler) / sizeof(*thread_handler);
	pthread_t tids[THDNO];
	int index;

#if 0
	globalmem.mem = (char *)malloc(BUFF_SIZE);
	globalmem.memsize = BUFF_SIZE;
	globalmem.mutex = pthread_mutex_init(&globalmem.mutex, NULL);
#endif

	for (index = 0; index < THDNO; index ++) {
		pthread_create(tids+index, NULL, thread_handler[index], (void *)index);
	}

	for (index = 0; index < THDNO; index ++)
		pthread_join(tids[index], NULL);
	
	return 0;
}

void * pthread_reader(void *arg)
{
	int no = (int)arg;

	while (1) {
		pthread_mutex_lock(&globalmem.mutex);
		pthread_cond_wait(&globalmem.cond, &globalmem.mutex);
		printf("reader%d:\n", no);
		puts(globalmem.mem);
		pthread_mutex_unlock(&globalmem.mutex);
		sleep(1);
	}
}

void * pthread_writer(void *arg)
{
	int counter = 0;
	
	while (1) {
//		pthread_mutex_lock(&globalmem.mutex);
		sprintf(globalmem.mem, "writer ---------- %d", counter ++);
		sleep(1);
		strcat(globalmem.mem, " *********");
#if 0
		pthread_cond_signal(&globalmem.cond);
		pthread_cond_signal(&globalmem.cond);
		pthread_cond_signal(&globalmem.cond);
		pthread_cond_signal(&globalmem.cond);
#endif
		pthread_cond_broadcast(&globalmem.cond);
//		pthread_mutex_unlock(&globalmem.mutex);
		sleep(1);
	}
}
