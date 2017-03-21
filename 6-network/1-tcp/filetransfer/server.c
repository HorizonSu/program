#include "head.h"

int ser_network_init(void);
int ser_upload(int connfd, const char *fname);
int ser_download(int connfd, const char *fname);

int main()
{
	int sockfd;
	int connfd;
	fmsg_t buff;
	
	if (-1 == (sockfd = ser_network_init()))
		error_exit("ser_network_init");

	while (1) {
		if (-1 == (connfd = accept(sockfd, NULL, NULL)))
			error_exit("accept");

		if (-1 == recv(connfd, &buff, offsetof(fmsg_t, fdata), 0))
			error_exit("recv");

		if (buff.fcmd == FCMD_UPLOAD)
			ser_upload(connfd, buff.fname);
		else if (buff.fcmd == FCMD_DOWNLOAD) {
			ser_download(connfd, buff.fname);
		}
		close(connfd);
	}
	
	close(sockfd);
	return 0;
}

int ser_network_init(void)
{
	int sockfd;
	struct sockaddr_in seraddr;

	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
		return -1;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
	if (-1 == bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		return -1;

	if (-1 == listen(sockfd, 128))
		return -1;
	
	return sockfd;
}

int ser_upload(int connfd, const char *fname)
{
	int fd;
	fmsg_t buff;
	
	if (-1 == (fd = open(fname, O_CREAT | O_WRONLY, 0644)))
		return -1;
	
	while (0 < recv(connfd, &buff, sizeof(buff), 0)) {
		if (-1 == write(fd, buff.fdata, buff.fbsize))
			return -1;
	}

	close(fd);
	
	return 0;
}

int ser_download(int connfd, const char *fname)
{
	int fd;
	int nbyte;
	fmsg_t buff;
	
	if (-1 == (fd = open(fname, O_RDONLY))) {
		buff.fcmd = FCMD_ERROR;
		send(connfd, &buff, offsetof(fmsg_t, fdata), 0);
		return 0;
	}

	while (0 < (nbyte = read(fd, buff.fdata, FBLOCK_SIZE))) {
		buff.fbsize = nbyte;
		if (-1 == send(connfd, &buff, sizeof(buff), 0))
			return -1;
	}

	close(fd);

	return 0;
}
