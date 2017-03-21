#include "head.h"

int main()
{
    int sockfd;
    struct sockaddr_in peeraddr,
                       mcast;
	char buff[BUFF_SIZE];
	int nbytes;
	socklen_t addrlen = sizeof(struct sockaddr);
	struct ip_mreqn mcaddr;
    
    if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) 
        error_exit("socket");

	mcast.sin_family = AF_INET;
	mcast.sin_port = htons(MCAST_PORT);
	mcast.sin_addr.s_addr = inet_addr(MCAST_ADDR); // INADDR_ANY;

    if (-1 == bind(sockfd, (struct sockaddr *)&mcast, sizeof(mcast)))
        error_exit("bind");

	mcaddr.imr_multiaddr.s_addr = inet_addr(MCAST_ADDR);
	mcaddr.imr_address.s_addr = inet_addr("192.168.0.17");	//INADDR_ANY;
	mcaddr.imr_ifindex = 0;
	
	if (-1 == setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mcaddr, sizeof(mcaddr)))
		error_exit("setsockopt");
	
	while (1) {
		memset(buff, 0, BUFF_SIZE);
		if (0 >= (nbytes = recvfrom(sockfd, buff, BUFF_SIZE, 0, 
						(struct sockaddr *)&peeraddr, &addrlen)))
			error_exit("recvfrom");
		printf("%s:%d->", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
		printf("%s\n", buff);
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

