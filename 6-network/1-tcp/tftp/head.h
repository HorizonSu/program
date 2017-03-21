#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#define N	1024

#define DATA_TYPE 	'D'
#define CMD_LIST	'l'
#define CMD_PUT		'p'
#define CMD_GET		'g'



#define FAMILY_TYPE		AF_INET

#define SER_PORT	10001
#define SER_ADDR	"192.168.1.10"
#define CLT_PORT	20002
#define CLT_ADDR	"192.168.1.200"

typedef struct sockaddr SA;
typedef struct _package_ {
	int type;
	int size;
	char data[N];
}DataPack;
