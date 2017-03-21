#include "head.h"

int main()
{
    int sockfd;
    struct sockaddr_in peeraddr,
                       bcast;
	char buff[BUFF_SIZE];
	int nbytes;
	socklen_t addrlen = sizeof(struct sockaddr);
    
    if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) 
        error_exit("socket");

	bcast.sin_family = AF_INET;
	bcast.sin_port = htons(BCAST_PORT);
	bcast.sin_addr.s_addr = inet_addr(BCAST_ADDR);

    if (-1 == bind(sockfd, (struct sockaddr *)&bcast, sizeof(bcast)))
        error_exit("bind");
	
	while (1) {
		memset(buff, 0, BUFF_SIZE);
		if (0 >= (nbytes = recvfrom(sockfd, buff, BUFF_SIZE, 0, 
						(struct sockaddr *)&peeraddr, &addrlen)))
			error_exit("recvfrom");
		printf("[%d]%s\n", nbytes, buff);
	}

#if 0
	strcat(buff, "---echo");
    if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0, 
			(struct sockaddr *)&peeraddr, sizeof(peeraddr)))
		error_exit("sendto");
#endif
	close(sockfd);

    return 0;
}

