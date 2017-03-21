#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <signal.h>

#define  error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define CLTADDR		"192.168.10.19"
#define CLTPORT		11111
#define SERADDR		"192.168.10.19"
#define SERPORT		20002
#define BUFFSIZE	1024

#endif
