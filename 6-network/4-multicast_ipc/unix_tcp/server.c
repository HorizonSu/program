#include "head.h"

int main()
{
	int sockfd,
		connfd;
	struct sockaddr_un seraddr,
					   cltaddr;
	socklen_t addrlen = sizeof(cltaddr);
	char buff[BUFF_SIZE];
	int flag = 1;	/* argument for setsockopt, SO_REUSEADDR */
	
	if (-1 == (sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)))
		error_exit("sockfd");
	
	seraddr.sun_family = AF_LOCAL;
	strcpy(seraddr.sun_path, SERADDR);

	if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)))
		error_exit("setsockopt");
	
	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("bind");

	if (-1 == listen(sockfd, 10))
		error_exit("listen");

	if (-1 == (connfd = accept(sockfd, (struct sockaddr *)&cltaddr, &addrlen)))
		error_exit("accept");

	if (0 >= recv(connfd, buff, BUFF_SIZE, 0))
		error_exit("recv");
	printf("recv:%s\n", buff);
	
	strcat(buff, "------echo");
	if (-1 == send(connfd,  buff, strlen(buff)+1, 0))
		error_exit("send");

	close(connfd);
	close(sockfd);

	return 0;

}
