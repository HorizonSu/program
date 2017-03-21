#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>

#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define SER_PORT		10001
#define SER_ADDR		"192.168.1.2"

#define BUFF_SIZE		1024

#endif
