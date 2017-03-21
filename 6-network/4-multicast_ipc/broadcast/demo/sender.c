#include "head.h"

int main()
{
    int sockfd;
    struct sockaddr_in bcastaddr;
	char *buff = NULL;
	int nbytes;
	int f_isbcast;
	time_t time_sec;
    
    if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) 
        error_exit("socket");

	f_isbcast = 1;
	if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, 
				&f_isbcast, sizeof(f_isbcast)))
		error_exit("setsockopt");

	bcastaddr.sin_family = AF_INET;
	bcastaddr.sin_port = htons(BCAST_PORT);
	bcastaddr.sin_addr.s_addr = inet_addr(BCAST_ADDR);

    if (-1 == connect(sockfd, (struct sockaddr *)&bcastaddr, sizeof(bcastaddr)))
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

