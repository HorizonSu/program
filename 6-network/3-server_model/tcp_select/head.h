#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define SER_PORT	50000
#define SER_ADDR	"192.168.1.86"

#define CLT_PORT	50001
#define CLT_ADDR	SER_ADDR

#define BUFF_SIZE	(1 << 10)

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)


#define DEBUG	1

#endif	/* __HEAD_H__ */
