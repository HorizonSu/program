#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_un peeraddr,
					   myaddr;

	char buff[BUFF_LEN];

	if( 0 > (sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0)))
		error_handler("socket");

	memset(&myaddr, 0, sizeof(SA_UN));
	myaddr.sun_family = AF_LOCAL;
	strcpy(myaddr.sun_path, SEND_PATH);

	memset(&peeraddr, 0, sizeof(peeraddr));
	peeraddr.sun_family = AF_LOCAL;
	strcpy(peeraddr.sun_path, RECV_PATH);

	unlink(myaddr.sun_path);

	if(0 > bind(sockfd, (SA *)&myaddr, sizeof(SA_UN)))
		error_handler("bind");

	while(1)
	{
		fgets(buff, BUFF_LEN, stdin);
		if( 0 > sendto(sockfd, buff, strlen(buff)+1, 0, (SA *)&peeraddr, sizeof(SA_UN)))
			error_handler("sendto");
		if( 0 > recvfrom(sockfd, buff, BUFF_LEN, 0, NULL, NULL))
			error_handler("recvfrom");
		puts(buff);
	}
	return 0;
}
