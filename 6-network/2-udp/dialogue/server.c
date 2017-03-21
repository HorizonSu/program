#include "head.h"

int main()
{
	pid_t pid;
	int sockfd;
	struct sockaddr_in seraddr,
					   cltaddr;
	char buff[BUFFSIZE];
	socklen_t addrlen = sizeof(struct sockaddr);

	
	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		error_exit("socket");

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SERPORT);
	seraddr.sin_addr.s_addr = inet_addr(SERADDR);
	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("bind");
	
	if (-1 == recvfrom(sockfd, buff, BUFFSIZE, 0, 
				(struct sockaddr *)&cltaddr, &addrlen))
		error_exit("recvfrom");
	printf("recvfrom->%s:%d\n", 
			inet_ntoa(cltaddr.sin_addr), ntohs(cltaddr.sin_port));
	printf("<<%s", buff);

	if (-1 == (pid = fork()))
		error_exit("fork");

	if (0 == pid) {
		while (1) {
			if (-1 == recvfrom(sockfd, buff, BUFFSIZE, 0, 
						(struct sockaddr *)&cltaddr, &addrlen))
				error_exit("recvfrom");
	
			printf("recvfrom->%s:%d\n", 
				inet_ntoa(cltaddr.sin_addr), ntohs(cltaddr.sin_port));

			printf("<<%s", buff);
		}
	} else {
		while (1) {
			printf(">>");
			fflush(stdout);
			fgets(buff, BUFFSIZE, stdin);
			if (!strcmp("#quit\n", buff)) {
				kill(pid, SIGKILL);
				exit(EXIT_SUCCESS);
			}
			printf("sendo->%s:%d\n",
				inet_ntoa(cltaddr.sin_addr), ntohs(cltaddr.sin_port));
			if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0,
						(struct sockaddr *)&cltaddr, sizeof(cltaddr)))
				error_exit("sendto");
		}
	}
	close(sockfd);
	return 0;
}
