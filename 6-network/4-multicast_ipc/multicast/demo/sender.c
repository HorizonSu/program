#include "head.h"

int main()
{
    int sockfd;
    struct sockaddr_in mcastaddr;
	char *buff = NULL;
	int nbytes;
	time_t time_sec;
    
    if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) 
        error_exit("socket");

	mcastaddr.sin_family = AF_INET;
	mcastaddr.sin_port = htons(MCAST_PORT);
	mcastaddr.sin_addr.s_addr = inet_addr(MCAST_ADDR);

    if (-1 == connect(sockfd, (struct sockaddr *)&mcastaddr, sizeof(mcastaddr)))
        error_exit("bind");

	time(&time_sec);
	while (2)  {
		sleep(1);
		time_sec ++;
		buff = ctime(&time_sec);
		printf("%s", buff);
		if (-1 == send(sockfd, buff, strlen(buff), 0))
			error_exit("send");
	}
	close(sockfd);

	return 0;
}

