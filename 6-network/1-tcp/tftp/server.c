#include "head.h"

int main()
{
	int sockfd;
	int connfd;
	int addrlen = sizeof(SA);
	struct sockaddr_in  serveraddr,
						clientaddr;
	int ret;
	DataPack *package = NULL;

	package = (DataPack *)malloc(sizeof(DataPack));

	if (0 > (sockfd = socket(FAMILY_TYPE, SOCK_STREAM, 0))) {
		perror("fail to open socket");
		return errno;
	}

	memset(&serveraddr, 0, sizeof(SA));
	memset(&clientaddr, 0, sizeof(SA));
	serveraddr.sin_family = FAMILY_TYPE;
	serveraddr.sin_port = htons(SER_PORT);
	serveraddr.sin_addr.s_addr = 0;

	if (0 > bind(sockfd, (SA *)&serveraddr, sizeof(SA))) {
		perror("fail to bind");
		return errno;
	}
	printf("bind->\t%s:%d\n",SER_ADDR,SER_PORT);

	if (0 > listen(sockfd, 5)) {
		perror("fail to listen");
		return errno;
	}
	printf("listen->\t%s:%d\n",SER_ADDR,SER_PORT);

	while (0 < (connfd = accept(sockfd, (SA *)&clientaddr, &addrlen))) {
		printf("accept->\t%s:%d\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		if (0 > (ret = recv(connfd, package, sizeof(DataPack), 0))) {
			perror("fail to recv");
			return errno;
		}
		printf("main->received bytes : %d\n", ret);

		switch(package->type) {
		case CMD_LIST:
			list_to_client(connfd, package);
			break;
		case CMD_PUT:
			file_from_client(connfd, package);
			break;
		case CMD_GET:
			file_to_client(connfd, package);
			break;
		default :
			puts("unknow command");
			continue;
		}
		close(connfd);
	}
	
	close(sockfd);
	free(package);
	return 0;
}

int file_to_client(int connfd, DataPack * package)
{
	FILE *fp = NULL;
	int nbyte = 0;

	printf("send to client : [%s]\n", package->data);
	
	if (NULL == (fp = fopen(package->data,"r"))) {
		perror("fail to open file");
		return errno;
	}

	if (0 < (nbyte = fread(package->data, 1, N, fp))) {
		printf("read bytes : %d\n", nbyte);
		if (0 > (nbyte = send(connfd, package, nbyte + 9, 0))) {
			perror("fail to send data");
			return errno;
		}
		printf("send bytes : %d\n", nbyte);
	}
	
	return 0;
}

int file_from_client(int connfd, DataPack *package)
{
	FILE *fp = NULL;
	int ret;

	printf("receive from client : [%s]\n", package->data);
	
	if (NULL == (fp = fopen(package->data, "w"))) {
		printf("fail to open %s", package->data);
		perror(" ");
		return errno;
	}
	
	memset(package, 0, sizeof(DataPack));
	while (8 < (ret = recv(connfd, package, sizeof(DataPack), 0))) {
		printf("received bytes [%d]:%s\n",ret, package->data);
		fwrite(package->data, ret - 8, 1, fp);
//		puts(package->data);
	}
	fclose(fp);
	return 0;
}


int list_to_client(int connfd, DataPack* package)
{
	DIR *mydir = NULL;
	struct dirent *mydirent;
	int ret;
	
	if (NULL == (mydir = opendir("."))) {
		perror("fail to open dir");
	 	return errno;
	}
	
	package->data[0] = 0;
	while (NULL != (mydirent = readdir(mydir))) {
		strcat(package->data, mydirent->d_name);
		strcat(package->data, "\t");
	}
	
	package->type = DATA_TYPE;
	package->size = strlen(package->data) + 1;

	printf("package->size : %d\n", package->size);
	if (0 > (ret = send(connfd, package, package->size + 8, 0))) { 
		perror("fail to send");
		return errno;
	}
	printf("send bytes : %d\n", ret);	

	return 0;
}
