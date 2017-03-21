/* interthread communication */


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE	128

typedef struct _global_mem_ {
	char buff[BUFF_SIZE];
}gmem_t;

gmem_t globamem = {
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

	for (index = 0; index < THDNO; index ++)
		pthread_create( tids+index, NULL, pthread_handlers[index], NULL);

	for (index = 0; index < THDNO; index ++)
		pthread_join(tids[index], NULL);

	return 0;
}

void * reader(void *arg)
{
	while (1)
	{
		printf("read:	%s\n", globamem.buff);
		sleep(1);
	}

	return NULL;
}

void * writer(void *arg)
{
	while (1)
	{
		puts("copy:");
		strcpy(globamem.buff, "hello");
		sleep(1);
		puts("cat");
		strcat(globamem.buff, "----------------------------world");
		sleep(1);
	}

	return NULL;
}
