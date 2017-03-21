#ifndef __ARP_H__
#define __ARP_H__

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include "netdevice.h"

#define error_exit(_errmsg_)    error(EXIT_FAILURE, errno, _errmsg_)

/* for arp packet */
#define MAC_LEN		6
#define IP4_LEN		4
#define GATEWAY		"192.168.0.1"
#define DEV_NAME	"eth0"

/* nonzero for enable, then show debug message */
#define DEBUG	0
/* generic buffer size */
#define BUFF_SIZE	1024

/* for attack type, in program */
#define ATK_SINGLE	'1'
#define ATK_WHITE	'w'
#define ATK_BLACK	'b'

/* for key word, in configuration file */
#define CFG_KEY_WHITE	"white\n"
#define CFG_KEY_BLACK	"black\n"
#define CFG_FILE_PATH	"./.atklist.info"

typedef struct _attack_lists_{
	int atk_type;				/* the type of attack*/
	int atk_num;				/* the numbers of ip address */
	struct in_addr *atk_list;	/* which ip do you want to attack, in network byte order*/
}atklist_st;

extern int send_arp(int sockfd, struct in_addr sender, struct in_addr target);
extern int arp_attack(atklist_st *atklist);
extern int get_attack_config(atklist_st *atklist, int atk_type);
extern int delete_ip(atklist_st *atklist, struct in_addr ip);
extern int get_all_atkip(atklist_st *atklist);


#endif /* __ARP_H__ */
