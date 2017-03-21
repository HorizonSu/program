#include "head.h"

int main()
{
	pid_t pid;
	int sockfd;
	struct sockaddr_in seraddr,
						  cltaddr;
	char buff[BUFFSIZE];

	cltaddr.sin_family = AF_INET;
	cltaddr.sin_port = htons(CLTPORT);
	cltaddr.sin_addr.s_addr = inet_addr(CLTADDR);

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SERPORT);
	seraddr.sin_addr.s_addr = inet_addr(SERADDR);
	
	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		error_exit("socket");

	if (-1 == bind(sockfd, (struct sockaddr *)&cltaddr, sizeof(cltaddr)))
		error_exit("bind");

	if (-1 == (pid = fork()))
		error_exit("fork");

	if (0 == pid) {
		while (1) {
			memset(buff, 0, BUFFSIZE);
			if (-1 == recvfrom(sockfd, buff, BUFFSIZE, 0, NULL, NULL))
				error_exit("recvfrom");
			printf("<<%s", buff);
		}
	} else {
		while (1) {
			printf(">>");
			fflush(stdout);
			fgets(buff, BUFFSIZE, stdin);
			if (!strcmp("#quit\n", buff)) {
				kill(pid, SIGKILL);
				exit(EXIT_FAILURE);
			}
			if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0, (struct sockaddr *)&seraddr, sizeof(seraddr)))
				error_exit("sendto");
		}
	}

	close(sockfd);
	return 0;
}
