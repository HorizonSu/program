#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/user.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <signal.h>

#define ERROR(_errmsg_)	error(EXIT_FAILURE, errno, "%s:%d->%s\n",\
		__FILE__, __LINE__, _errmsg_)

#define MEM_SIZE	PAGE_SIZE
#define KEY_VALUE	0X0102333

#define BUFF_SIZE	1024

typedef struct _mesginfo_{
	int pidw;
	int pidr;
	char buff[BUFF_SIZE];
}mesg_t;

#endif
