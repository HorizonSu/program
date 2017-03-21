/* using shared memory and signal */

#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <sys/user.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

typedef struct _mesg_pack_ {
	pid_t pida,
		  pidb;
	int value;
}mesg_st;

#define KEY_VALUE	0X01020304
#define MEM_SIZE	PAGE_SIZE

#endif
