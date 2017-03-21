#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_in seraddr,
					   cltaddr;
	char buff[BUFF_SIZE];
	int ret;
	socklen_t addrlen = sizeof(cltaddr);
	
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		error_exit("socket");

	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("bind");

	while (1) {
		memset(buff, 0, BUFF_SIZE);
		if (-1 == (ret = recvfrom(sockfd, buff, BUFF_SIZE, 0,
						(struct sockaddr *)&cltaddr, &addrlen)))
			error_exit("recvfrom");
		printf("%s:%d->%s\n", 
				inet_ntoa(cltaddr.sin_addr), ntohs(cltaddr.sin_port), buff);

		if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0,
					(struct sockaddr *)&cltaddr, sizeof(cltaddr)))
			error_exit("sendto");
	}
	close(sockfd);

	return 0;
}
