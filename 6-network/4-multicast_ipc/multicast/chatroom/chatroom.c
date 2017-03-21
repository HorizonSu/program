#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stddef.h>
#include <time.h>
#include "protocol.h"

#define BUFF_SIZE	4096
#define error_exit(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

typedef struct sockaddr sockaddr_t;
struct sockaddr_in mcastaddr;
cmsg_t buff;

int chat_network_init(void);
int chat_login(int sockfd);
int chat_logout(int sockfd);
char *chat_get_time(void);
int chat_print_tittle(const char *usr, const char *date, const char *ip);
int chat_print_text(const char *text);

int main()
{
	pid_t pid;
	int sockfd;
	struct sockaddr_in peeraddr;
	socklen_t addrlen = sizeof(peeraddr);

	if (-1 == (sockfd = chat_network_init()))
		error_exit("chat_network_init");
	
	chat_login(sockfd);

	if (-1 == (pid = fork()))
		error_exit("fork");

	/* father, send */
	if (pid > 0) {
		while (1) {
			fgets(buff.ch_text, CHAT_MESG_TEXT_LEN, stdin);
			buff.ch_text[strlen(buff.ch_text)-1] = '\0';

			if (!strcmp(buff.ch_text, "#")) {
				chat_logout(sockfd);
				kill(pid, SIGKILL);
				exit(EXIT_SUCCESS);
			}
			
			buff.ch_type = CHAT_MESG_NOMAL;
			if (-1 == sendto(sockfd, &buff, sizeof(buff), 0,
					(sockaddr_t *)&mcastaddr, sizeof(mcastaddr)))
				error_exit("sendto");
		}

	/* child, receive */
	} else {
		while (1) {
			if (-1 == recvfrom(sockfd, &buff, sizeof(buff), 0, (sockaddr_t *)&peeraddr, &addrlen))
				error_exit("recvfrom");
			
			switch (buff.ch_type) {
			case CHAT_MESG_NOMAL:
				chat_print_tittle(buff.ch_name, chat_get_time(), inet_ntoa(peeraddr.sin_addr));
				chat_print_text(buff.ch_text);
				break;
			case CHAT_MESG_LOGIN:
				chat_print_tittle("system", chat_get_time(), inet_ntoa(peeraddr.sin_addr));		
				sprintf(buff.ch_text, "%s Login !", buff.ch_name);
				chat_print_text(buff.ch_text);
				break;
			case CHAT_MESG_LOGOUT:
				chat_print_tittle("system", chat_get_time(), inet_ntoa(peeraddr.sin_addr));		
				sprintf(buff.ch_text, "%s Logout !", buff.ch_name);
				chat_print_text(buff.ch_text);
				break;
			default:
				break;
			}
		}
	}
	
	return 0;
}

int chat_network_init(void)
{
	int sockfd;
	int is_bacst = 1;
	struct ip_mreqn mcast_iface;

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		return -1;

	mcast_iface.imr_multiaddr.s_addr = inet_addr(CHAT_COMM_ADDR);
	mcast_iface.imr_address.s_addr = INADDR_ANY; //inet_addr("192.168.1.3");
	mcast_iface.imr_ifindex = 0;
	if (-1 == setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcast_iface, sizeof(mcast_iface)))
		error_exit("setsockopt");
	
	mcastaddr.sin_family = AF_INET;
	mcastaddr.sin_port = htons(CHAT_COMM_PORT);
	mcastaddr.sin_addr.s_addr = inet_addr(CHAT_COMM_ADDR);
	if (-1 == bind(sockfd, (sockaddr_t *)&mcastaddr, sizeof(mcastaddr)))
		return -1;
	
	return sockfd;
}

int chat_login(int sockfd)
{
	puts("enter your name:");
	fgets(buff.ch_name, CHAT_MESG_NAME_LEN, stdin);
	buff.ch_name[strlen(buff.ch_name)-1] = '\0';
	buff.ch_type = CHAT_MESG_LOGIN;

	if (-1 == sendto(sockfd, &buff, offsetof(cmsg_t, ch_text), 0, 
			(sockaddr_t *)&mcastaddr, sizeof(mcastaddr)))
		return -1;

	return 0;
}

int chat_logout(int sockfd)
{
	buff.ch_type = CHAT_MESG_LOGOUT;

	if (-1 == sendto(sockfd, &buff, offsetof(cmsg_t, ch_text), 0, 
			(sockaddr_t *)&mcastaddr, sizeof(mcastaddr)))
		return -1;

	return 0;
	
}

char *chat_get_time(void)
{
	time_t tm_sec;
	struct tm *tm_buff;
	static char tm_str[128];

	time(&tm_sec);
	tm_buff = localtime(&tm_sec);
	
	sprintf(tm_str, "%d/%d/%d %d:%d:%d", 
			tm_buff->tm_year+1900, tm_buff->tm_mon+1, tm_buff->tm_mday,
			tm_buff->tm_hour, tm_buff->tm_min, tm_buff->tm_sec);

	return tm_str;
}

int chat_print_tittle(const char *usr, const char *date, const char *ip)
{
	printf("\e[1;31m%s\e[0m@\e[1;32m%s\e[34m[%s]\e[0m\n", usr, date, ip);

	return 0;
}

int chat_print_text(const char *text)
{
	printf("\t\e[1;33m%s\e[0m\n", text);

	return 0;
}
