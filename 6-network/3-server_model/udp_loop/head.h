#ifndef __HEAD_H__
#define __HEAD_H__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)
#define BUFF_SIZE	1024
#define CLT_PORT		10001
#define CLTADDR		"192.168.10.19"
#define SER_PORT		50000
#define SER_ADDR		"192.168.100.1"

#endif	/* __HEAD_H__ */
