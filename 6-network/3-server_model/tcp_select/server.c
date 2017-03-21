#include "head.h"

int process(int sockfd, fd_set *fds);

int main()
{
	int sockfd;
	int connfd;
	int maxfd;
	int fd;
	struct sockaddr_in seraddr,
					   cltaddr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	fd_set rdfds,
		   tmpfds;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = 0;

	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
		error_exit("socket");

	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("bind");
	
	if (-1 == listen(sockfd, 128))
		error_exit("listen");

	FD_ZERO(&tmpfds);
	FD_SET(sockfd, &tmpfds);
	maxfd = sockfd;

	while (1) {
		rdfds = tmpfds;
		if (-1 == select(maxfd + 1, &rdfds, NULL, NULL, NULL))
			error_exit("select");

		if (FD_ISSET(sockfd, &rdfds)) {
			if (-1 == (connfd = accept(sockfd, (struct sockaddr *)&cltaddr, &addrlen)))
				error_exit("accept");
			FD_SET(connfd, &tmpfds);
			maxfd = connfd > maxfd ? connfd : maxfd;
#if DEBUG
			printf("fd: %d\n", connfd);
#endif
		}

		for (fd = sockfd + 1; fd <= maxfd; fd ++) {
			if (FD_ISSET(fd, &rdfds))
				process(fd, &tmpfds);
		}
	}

	close(sockfd);
	close(connfd);

	return 0;
}

int process(int sockfd, fd_set *fds)
{
	time_t tim_sec;
	char buff[BUFF_SIZE];

	if (0 < recv(sockfd, &tim_sec, sizeof(tim_sec), 0)) {
		tim_sec = ntohl(tim_sec);
		strcpy(buff, ctime(&tim_sec));

		if (-1 == send(sockfd, buff, strlen(buff) + 1, 0))
			error_exit("send");

	/* error handler */
	} else {
		close(sockfd);
		FD_CLR(sockfd, fds);
	}

	return 0;
}
