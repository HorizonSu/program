#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)
#define BUFF_SIZE	1024
#define SERADDR		"/tmp/unix_tcpserver"

#endif
