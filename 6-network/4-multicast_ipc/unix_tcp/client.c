#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_un seraddr,
					   cltaddr;
	char buff[BUFF_SIZE];
	
	if (-1 == (sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)))
		error_exit("socket");

	seraddr.sun_family = AF_LOCAL;
	strcpy(seraddr.sun_path, SERADDR);

	if (-1 == connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("connect");

	strcpy(buff, "helloworld");
	if (-1 == send(sockfd, buff, strlen(buff)+1, 0))
		error_exit("send");

	memset(buff, 0, BUFF_SIZE);
	if (0 >= recv(sockfd, buff, BUFF_SIZE, 0))
		error_exit("recv");

	printf("%s\n", buff);
	close(sockfd);

	return 0;
}
