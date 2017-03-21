#include "head.h"

int clt_network_init(void);
int clt_upload(int sockfd, const char *fname);
int clt_download(int sockfd, const char *fname);

int main(int argc, const char *argv[])
{
	int sockfd;
	
	if (argc != 3)
		error_exit("invalid arguments");

	if (-1 == (sockfd = clt_network_init()))
		error_exit("network_init");
	
	if (!strncmp(argv[1], "-up", 4)) {
		if (-1 == clt_upload(sockfd, argv[2]))
			error_exit("clt_upload");
	} else if (!strncmp(argv[1], "-down", 6)) {
		if (-1 == clt_download(sockfd, argv[2]))
			error_exit("clt_download");
	} else
		printf("invalid argument of '%s'\n", argv[1]);

	close(sockfd);

	return 0;
}

int clt_network_init(void)
{
	int sockfd;
	struct sockaddr_in seraddr;

	if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
		return -1;

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
	if (-1 == connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		return -1;

	return sockfd;
}

int clt_upload(int sockfd, const char *fname)
{
	int fd;
	int nbyte;
	fmsg_t buff;
	
	if (-1 == (fd = open(fname, O_RDONLY)))
		return -1;

	buff.fcmd = FCMD_UPLOAD;
	strcpy(buff.fname, fname);
	if (-1 == send(sockfd, &buff, offsetof(fmsg_t, fdata), 0))
		return -1;

	while (0 < (nbyte = read(fd, buff.fdata, FBLOCK_SIZE))) {
		buff.fbsize = nbyte;
		if (-1 == send(sockfd, &buff, sizeof(buff), 0))
			return -1;
	}

	close(fd);

	return 0;
}

int clt_download(int sockfd, const char *fname)
{
	int fd;
	fmsg_t buff;
	
	if (-1 == (fd = open(fname, O_CREAT | O_WRONLY, 0644)))
		return -1;
	
	buff.fcmd = FCMD_DOWNLOAD;
	strcpy(buff.fname, fname);
	if (-1 == send(sockfd, &buff, offsetof(fmsg_t, fdata), 0))
		return -1;

	while (0 < recv(sockfd, &buff, sizeof(buff), 0)) {
		if (buff.fcmd == FCMD_ERROR) {
			printf("error when downloading %s\n", fname);
			break;
		}
		if (-1 == write(fd, buff.fdata, buff.fbsize))
			return -1;
	}

	close(fd);
	
	return 0;
}
