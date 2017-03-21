/* using shared memory and semaphore */

#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>


#define error_exit(_errmsg_) 	error(EXIT_FAILURE, errno, _errmsg_)
	
#define SHM_SIZE 	4096
#define KEY_VALUE 	0x01020304
#define SEM_READ 	"sem_read"
#define SEM_WRITE 	"sem_write"

typedef struct _mesginfo_ {
	pid_t pidw,
		  pidr;
	int value;
}mesg_st;

#endif /* __HEAD_H__ */
