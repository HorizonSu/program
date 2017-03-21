#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define BCAST_PORT    50001
#define BCAST_ADDR    "192.168.10.255"

#define error_exit(_errmsg_)    error(EXIT_FAILURE, errno, _errmsg_)

#define BUFF_SIZE	1024



#endif /* __HEAD_H__ */
