#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define THD_LED		0
#define THD_GPRS	1
#define THD_CAME	2
#define THD_FIRE	3
#define THD_ALARM	4

#define WARN_FIRE	'F'
#define WARN_THIEF	'T'

typedef struct _pthead_info_ {
	pthread_t tid;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	void *arg;
}thdinfo_t;

void *led_cntl(void *arg);
void *gprs_cntl(void *arg);
void *camera_cntl(void *arg);
void *firehydrant_cntl(void *arg);
void *alarm_cntl(void *arg);

int warn_flag;


int main()
{
	void *(*pthread_handlers[])(void *) = {
		led_cntl,
		gprs_cntl,
		camera_cntl,
		firehydrant_cntl,
		alarm_cntl,
	};
	const int THDNO = sizeof(pthread_handlers) / sizeof(*pthread_handlers);
	thdinfo_t *thdinfo_buff = NULL;
	int index;
	char cmd[16];

	thdinfo_buff = (thdinfo_t *)malloc(sizeof(thdinfo_t) * THDNO);

	for (index = 0; index < THDNO; index ++) {
		pthread_mutex_init(&thdinfo_buff[index].mutex, NULL);
		pthread_cond_init(&thdinfo_buff[index].cond, NULL);
	}

	for (index = 0; index < THDNO; index ++)
		pthread_create( &thdinfo_buff[index].tid, NULL, pthread_handlers[index], thdinfo_buff + index);

	while (1) {
		puts("enter your command:");
		fgets(cmd, 16, stdin);
		switch (cmd[0]) {
		case 'f':
			warn_flag = WARN_FIRE;
			pthread_cond_signal(&thdinfo_buff[THD_GPRS].cond);
			pthread_cond_signal(&thdinfo_buff[THD_ALARM].cond);
			pthread_cond_signal(&thdinfo_buff[THD_FIRE].cond);
			break;
		case 't':
			warn_flag = WARN_THIEF;
			pthread_cond_signal(&thdinfo_buff[THD_GPRS].cond);
			pthread_cond_signal(&thdinfo_buff[THD_ALARM].cond);
			pthread_cond_signal(&thdinfo_buff[THD_LED].cond);
			pthread_cond_signal(&thdinfo_buff[THD_CAME].cond);
			break;
		case 'c':
				warn_flag = 0;	
			break;
		case 'q':
			goto Quit;
		default: 
			puts("command error !");
			break;
		}
	}

	for (index = 0; index < THDNO; index ++)
		pthread_join(thdinfo_buff[index].tid, NULL);

Quit:
	for (index = 0; index < THDNO; index ++) {
		pthread_cancel(thdinfo_buff[index].tid);
	}
	free(thdinfo_buff);
	exit(EXIT_SUCCESS);
	return 0;
}

void *led_cntl(void *arg)
{
	thdinfo_t *info = arg;
	while (1) {

		pthread_mutex_lock(&info->mutex);
		pthread_cond_wait(&info->cond, &info->mutex);
		pthread_mutex_unlock(&info->mutex);
		
		while (warn_flag) {
			puts("---------- led -----------");
			sleep(1);
		}
	}
}

void *gprs_cntl(void *arg)
{
	thdinfo_t *info = arg;
	while (1) {

		pthread_mutex_lock(&info->mutex);
		pthread_cond_wait(&info->cond, &info->mutex);
		pthread_mutex_unlock(&info->mutex);
		
		while (warn_flag) {
			puts("---------- gprs -----------");
			sleep(1);
		}
	}
}

void *camera_cntl(void *arg)
{
	thdinfo_t *info = arg;
	while (1) {

		pthread_mutex_lock(&info->mutex);
		pthread_cond_wait(&info->cond, &info->mutex);
		pthread_mutex_unlock(&info->mutex);
		
		while (warn_flag) {
			puts("---------- camera -----------");
			sleep(1);
		}
	}
}

void *firehydrant_cntl(void *arg)
{
	thdinfo_t *info = arg;
	while (1) {

		pthread_mutex_lock(&info->mutex);
		pthread_cond_wait(&info->cond, &info->mutex);
		pthread_mutex_unlock(&info->mutex);
		
		while (warn_flag) {
			puts("---------- firehydrant  -----------");
			sleep(1);
		}
	}
}

void *alarm_cntl(void *arg)
{
	thdinfo_t *info = arg;
	while (1) {

		pthread_mutex_lock(&info->mutex);
		pthread_cond_wait(&info->cond, &info->mutex);
		pthread_mutex_unlock(&info->mutex);
		
		while (warn_flag) {
			puts("---------- alarm -----------");
			sleep(1);
		}
	}
}

