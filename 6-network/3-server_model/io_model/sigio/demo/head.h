#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <errno.h>

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define BUFF_SIZE	1024
#define FIFO_PATH	"/tmp/sigio_fifo"


#endif /* __HEAD_H__ */
