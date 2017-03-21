#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#if 0
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define BUFF_LEN	128
#define error_handler(MEsg)		\
	do{perror(MEsg);exit(1);	\
	}while(0);

#define SEND_PATH	"/tmp/unixsender"
#define RECV_PATH	"/tmp/unixreceiver"

typedef struct sockaddr	SA;
typedef struct sockaddr_un SA_UN;

