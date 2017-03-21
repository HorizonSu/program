#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

typedef struct _thread_args_ {
	int data;
	char buff[20];
	float f;
}threadarg_st;

/* for test pthread_exit  */
void fun(void)
{
	puts("----------------");
	pthread_exit(NULL);
	return -1;
}


void *thread1(void *argv)
{
	char *buff = NULL;
	threadarg_st *arg = argv;
	

	/* for test pthread_exit */
	fun();
	
	printf("data: %d\n", arg->data);
	printf("buff: %s\n", arg->buff);
	printf("f: %f\n", arg->f);
	return NULL;
}

int main()
{
	pthread_t tid;
	void *retval = NULL;
	threadarg_st buff = {
		.data = 10,
		.buff = "12345",
		.f = 3.1415,
	};

	if (0 != (errno = pthread_create(&tid, NULL, thread1, &buff)))
		perror("pthread_create");

	puts("main:");
	puts("helloworld");
	
	sleep(3);
	pthread_cancel(tid);

	pthread_join(tid, &retval);

	return 0;
}
