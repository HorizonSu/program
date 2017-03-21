#include "head.h"

int main()
{
	int sockfd,
		connfd;
	struct sockaddr_in seraddr;
	char *buff = NULL;

	buff = (char *)malloc(BUFF_SIZE);

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
		error_exit("socket");
	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("bind");

	if (-1 == listen(sockfd, 10))
		error_exit("listen");

	while (1)  {
		if (-1 == (connfd = accept(sockfd, NULL, NULL)))
			error_exit("accept");
		while (1) {
			if (0 >= recv(connfd, buff, BUFF_SIZE, 0))
				break;
			printf("recv: %s\n", buff);

			strcat(buff, "----echo");
			if (0 >= send(connfd, buff, strlen(buff)+1, 0))
				break;
		}
		close(connfd);
	}
	
	close(sockfd);
	free(buff);

	return 0;
}
