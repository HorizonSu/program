#include <stdio.h>
#include <pthread.h>
#include <errno.h>

typedef struct _operands_ {
	int opd1;
	int opd2;
}opd_st;

void *thread_add(void *arg)
{
	opd_st *opds = arg;
	printf("%d + %d = %d\n", opds->opd1, opds->opd2, 
			opds->opd1 + opds->opd2);
	return NULL;
}

void *thread_sub(void *arg)
{
	opd_st *opds = arg;
	printf("%d - %d = %d\n", opds->opd1, opds->opd2, 
			opds->opd1 - opds->opd2);
	return NULL;
}

void *thread_mul(void *arg)
{
	opd_st *opds = arg;
	printf("%d * %d = %d\n", opds->opd1, opds->opd2, 
			opds->opd1 * opds->opd2);
	return NULL;
}

void *thread_div(void *arg)
{
	opd_st *opds = arg;
	printf("%d / %d = %d\n", opds->opd1, opds->opd2, 
			opds->opd1 / opds->opd2);
	return NULL;
}

void *thread_rem(void *arg)
{
	opd_st *opds = arg;
	printf("%d %% %d = %d\n", opds->opd1, opds->opd2, 
			opds->opd1 % opds->opd2);
	return NULL;
}

int main()
{
	int index;
	opd_st opds = {
		.opd1 = 10,
		.opd2 = 100,
	};
	void *(*thread_handlers[])(void *) = {
		thread_add,
		thread_sub,
		thread_mul,
		thread_div,
		thread_rem,
	};
	const int THDNO = sizeof(thread_handlers) / sizeof (*thread_handlers);
	pthread_t tids[THDNO];

	for (index = 0; index < THDNO; index ++) {
		errno = pthread_create(tids+index, NULL, thread_handlers[index], &opds);
		if (0 != errno)
			perror("pthread_create");
	}

	for (index = 0; index < THDNO; index ++)
		pthread_join(tids[index], NULL);

	return 0;
}
