#include "head.h"

int connect_to_server(SA *addr);
int file_from_server(SA * addr, char *filename);

int main()
{
	int sockfd;
	struct sockaddr_in serveraddr;
	char cmd[128];

	
	memset(&serveraddr, 0, sizeof(SA));
	serveraddr.sin_family = FAMILY_TYPE;
	serveraddr.sin_port = htons(SER_PORT);
	serveraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	while (1) {
		puts("enter your command:");
		fgets(cmd, 128, stdin);
		cmd[strlen(cmd) - 1] = '\0';

		if ( ! strcmp(cmd, "list"))
			list_from_server((SA *)&serveraddr);
		else if ( ! strncmp(cmd, "put ", 4))
			file_to_server((SA *)&serveraddr, cmd + 4);
		else if ( ! strncmp(cmd, "get ", 4))
			file_from_server((SA *)&serveraddr, cmd + 4);
		else if ( ! strcmp(cmd, "quit"))
			break;
		else 
			puts("command error !");			
	}
	return 0;
}

int file_from_server(SA * addr, char *filename)
{
	int sockfd;
	int ret;
	DataPack *package = NULL;
	FILE *fp = NULL;
	puts("file from server:");

	package = (DataPack *)malloc(sizeof(DataPack));
	package->type = CMD_GET;
	strcpy(package->data, filename);
	package->size = strlen(filename) + 9;
	
	if (NULL == (fp = fopen(filename,"w"))) {
		perror("fail to open local new file");
		return errno;
	}
	
	sockfd = connect_to_server( addr );
	
	if (0 > (ret = send(sockfd, package, package->size, 0))) {
		perror("fail to send");
		return errno;
	}
	printf("send bytes : %d\n",ret);

	while (8 < (ret = recv(sockfd, package, sizeof(DataPack), 0))) {
		printf("received bytes : %d\n",ret);
		fwrite(package->data, ret - 8, 1, fp);
//		puts(package->data);
	}

	free(package);
	close(sockfd);

	puts("shutdown from server");
	
	return 0;
}

int file_to_server(SA * addr, char *filename)
{
	int sockfd;
	int ret;
	DataPack *package = NULL;
	FILE *fp = NULL;
	int nbyte = 0;

	puts("file to server:");

	package = (DataPack *)malloc(sizeof(DataPack));
	package->type = CMD_PUT;
	strcpy(package->data, filename);
	package->size = strlen(filename) + 9;

	printf("send to server : [%s]\n", package->data);
	
	sockfd = connect_to_server( addr );

	//open file to read 
	
	if (NULL == (fp = fopen(package->data, "r"))) {
		perror("fail to open file");
		return errno;
	}

	if (0 > (nbyte = send(sockfd, package, package->size, 0))) {
		perror("fail to send data");
		return errno;
	}

	if (0 < (nbyte = fread(package->data, 1, N, fp))) {
		printf("read bytes : %d\n", nbyte);
		if (0 > (nbyte = send(sockfd, package, nbyte + 8, 0))) {
			perror("fail to send data");
			return errno;
		}
		printf("send bytes : %d\n", nbyte);
	}
	close(sockfd);
	fclose(fp);	
	return 0;
}

int list_from_server(SA * addr)
{
	int sockfd;
	int ret;
	DataPack *package = NULL;

	package = (DataPack *)malloc(sizeof(DataPack));
	package->type = CMD_LIST;
	package->size = 8;
	
	sockfd = connect_to_server( addr );
	
	if (0 > (ret = send(sockfd, package, package->size, 0))) {
		perror("fail to send");
		return errno;
	}
	printf("send bytes : %d\n",ret);

	while (8 < (ret = recv(sockfd, package, sizeof(DataPack), 0))) {
		printf("receive bytes : %d\n", ret);
		puts(package->data);
	}
	
	free(package);
	close(sockfd);
	puts("shutdown from server");
	
	return 0;
}

int connect_to_server(SA *addr)
{
	int sockfd;
	
	if (0 > (sockfd = socket(FAMILY_TYPE, SOCK_STREAM, 0))) {
		perror("fail to open socket");
		return errno;
	}

#if 0
	if (0 > bind(sockfd, (SA *)&serveraddr), sizeof(SA)) {
		perror("fail to bind");
		return errno;
	}
#endif
	
	if (0 > connect(sockfd, addr, sizeof(SA))) {
		perror("fail to accept");
		return errno;
	}
	printf("connect->\t%s:%d\n",SER_ADDR,SER_PORT);
	
	return sockfd;
}

