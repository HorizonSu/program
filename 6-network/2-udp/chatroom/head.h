#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <error.h>
#include <time.h>

#define error_exit(_errmsg_) 	\
	error(EXIT_FAILURE, errno, _errmsg_)

#define DATA_BUFF_LEN	512
#define USER_NAME_LEN	32

#define CMD_LOGIN	'I'
#define CMD_LOGOUT	'o'
#define CMD_CHAT	'C'

#define SER_PORT	50000
#define SER_ADDR	"192.168.0.4"

typedef struct _mesg_package_{
	int type;
	char user[USER_NAME_LEN];
	char data[DATA_BUFF_LEN];
}mesgpack_st;

#endif
