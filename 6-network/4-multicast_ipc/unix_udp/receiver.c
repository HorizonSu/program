#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_un myaddr,
					   peeraddr;

	char buff[BUFF_LEN];
	int addrlen = sizeof(SA_UN);
	int opt = 1;

	if( 0 > (sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0)))
		error_handler("socket");
	
	memset(&myaddr, 0, sizeof(SA_UN));
	myaddr.sun_family = AF_LOCAL;
	strcpy(myaddr.sun_path, RECV_PATH);

//	unlink(myaddr.sun_path);

	if( 0 > bind(sockfd, (SA *)&myaddr, sizeof(SA_UN)))
		error_handler("bind");

	while(1)
	{
		if( 0 > recvfrom(sockfd, buff, BUFF_LEN, 0, (SA *)&peeraddr, &addrlen))
			error_handler("recvfrom");
		printf("[%s]:%s\n", peeraddr.sun_path, buff);
		strcat(buff, "world");
		if( 0 > sendto(sockfd, buff, strlen(buff)+1, 0, (SA *)&peeraddr, sizeof(peeraddr)))
			error_handler("sendto");
	}
	close(sockfd);
	return 0;
}
