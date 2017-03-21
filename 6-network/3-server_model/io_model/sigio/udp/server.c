#include "head.h"

void socket_iohandler(int sig);
int sockfd;
char *buff = NULL;

int main()
{
	struct sockaddr_in seraddr;
	int flag;

	buff = (char *)malloc(BUFF_SIZE);

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = 0;//inet_addr(SER_ADDR);

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		error_exit("socket");

	signal(SIGIO, socket_iohandler);
	flag = fcntl(sockfd, F_GETFL);
	flag |= O_ASYNC;
	fcntl(sockfd, F_SETFL, flag);
	fcntl(sockfd, F_SETOWN, getpid());

	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("bind");

	while (1) {
		puts(">");
		fgets(buff, BUFF_SIZE, stdin);
		fputs(buff, stdout);
	}

	close(sockfd);
	free(buff);
	
	return 0;
}

void socket_iohandler(int sig)
{
	struct sockaddr_in cltaddr;
	socklen_t addrlen = sizeof(cltaddr);
	int ret;

	if (-1 == (ret = recvfrom(sockfd, buff, BUFF_SIZE, 0,
					(struct sockaddr *)&cltaddr, &addrlen)))
		error_exit("recvfrom");

	printf("recvfrom: %s:%d\n", 
			inet_ntoa(cltaddr.sin_addr), ntohs(cltaddr.sin_port));
	printf("[%d]:%s\n", ret, buff);
	
	strcat(buff, "---------echo");
	if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0,
				(struct sockaddr *)&cltaddr, sizeof(cltaddr)))
		error_exit("sendto");
	
}
