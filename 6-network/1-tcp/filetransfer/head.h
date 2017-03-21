/*	Project: 	TFTP
 *	Author: 	james.feng
 *	Date:		2014.8.28
 *	Version:	v1.0
 *	Descryption:
 *	this is a simple implementation of TFTP.
 *	USAGE:
 *	for upload using "./client -up file"
 *	for download using "./client -down file"
 *	
 *
 *
 * */



#ifndef __HEAD_H__
#define __HEAD_H__

/* network */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

/* file IO */
#include <sys/stat.h>
#include <fcntl.h>

/* other */
#include <stddef.h>
#include <errno.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define FCMD_DOWNLOAD	'D'
#define FCMD_UPLOAD		'U'
#define FCMD_ERROR		'E'
#define FNAME_LEN	32
#define FBLOCK_SIZE	1024
#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define SER_PORT	10000
#define SER_ADDR	"192.168.1.3"

#endif	/* __HEAD_H__ */

typedef struct fs_proto {
	int fcmd;
	char fname[FNAME_LEN];
	int fbsize;
	char fdata[FBLOCK_SIZE];
}fmsg_t;
