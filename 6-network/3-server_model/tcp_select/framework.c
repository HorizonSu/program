


int main()
{
	int sockfd;
	
	sockfd = socket();
	bind();
	listen();
	
	FD_SET(sockfd, &rdfds);


	while (1) {
		select();
		
		if (FD_ISSET(sockfd, &rdfds)) {
			connfd = accept();
			FD_SET(connfd, &rdfds);
		} else {
			for (fd = 0; fd < 1024; fd ++) {
				if (FD_ISSET(fd, &rdfds)) {
					recv();
					process();
					send();
				}
			}
		}
	}
}
