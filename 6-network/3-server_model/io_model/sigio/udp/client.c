#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_in seraddr;
	char *buff = NULL;
	int ret;

	buff = (char *)malloc(BUFF_SIZE);

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		error_exit("socket");

	if (-1 == connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("connect");

	while (1) {
		puts(">");
		fgets(buff, BUFF_SIZE, stdin);
		if (-1 == send(sockfd, buff, strlen(buff)+1, 0))
			error_exit("send");
		if (-1 == (ret = recv(sockfd, buff, BUFF_SIZE, 0)))
			error_exit("recv");
		printf("[%d]:%s\n", ret, buff);
	}
	close(sockfd);
	free(buff);

	return 0;
}
