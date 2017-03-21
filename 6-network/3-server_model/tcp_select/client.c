#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_in seraddr;
	char *buff;
	time_t tim_sec;
	int ret;
	int i = 0;


	buff = malloc(BUFF_SIZE);

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
	
	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
		error_exit("socket");

	if (-1 == connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("connect");


	tim_sec = time(NULL);
	while (1) {
		strcpy(buff, ctime(&tim_sec));
		tim_sec ++;
		sleep(1);

		if (-1 == (ret = send(sockfd, buff, strlen(buff)+1, 0)))
			error_exit("send");
		printf("[%d] --- %s", i ++, buff);
	}

	close(sockfd);
	return 0;
}
