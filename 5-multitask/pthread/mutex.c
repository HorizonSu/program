#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE	128

typedef struct _global_mem_ {
	char buff[BUFF_SIZE];
	const int buffsize;
	pthread_mutex_t mutex;
}gmem_t;

gmem_t globamem = {
	.buffsize = BUFF_SIZE,
	.mutex = PTHREAD_MUTEX_INITIALIZER
};

void * reader(void *arg);
void * writer(void *arg);

int main()
{
	void *(*pthread_handlers[])(void *) = {
		reader, 
		writer,
	};
	const int THDNO = sizeof(pthread_handlers) / sizeof(*pthread_handlers);
	pthread_t tids[THDNO];
	int index;

//	pthread_mutex_init(&globamem.mutex, NULL);

	for (index = 0; index < THDNO; index ++)
		pthread_create( tids+index, NULL, pthread_handlers[index], NULL);

	for (index = 0; index < THDNO; index ++)
		pthread_join(tids[index], NULL);

	return 0;
}

void * reader(void *arg)
{
	while (1) {
		pthread_mutex_lock(&globamem.mutex);
	//	pthread_mutex_lock(&globamem.mutex);
		printf("read:	%s\n", globamem.buff);
		memset(globamem.buff, 0, BUFF_SIZE);
		pthread_mutex_unlock(&globamem.mutex);
		sleep(1);
	}

	return NULL;
}

void *writer(void *arg)
{
	while (1) {
		pthread_mutex_lock(&globamem.mutex);
		puts("copy:");
		strcpy(globamem.buff, "hello");
		puts("cat");
		sleep(1);
		strcat(globamem.buff, "----------------------------world");
		pthread_mutex_unlock(&globamem.mutex);

		sleep(1);
	}

	return NULL;
}
