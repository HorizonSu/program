#include "head.h"

#define IS_USE_CONNECT	1

int main()
{
	int sockfd;
	struct sockaddr_in seraddr,
					   cltaddr;
	char *buff = NULL;
	int ret;

	buff = (char *)malloc(BUFF_SIZE);

	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		error_exit("socket");
#if 0
	/* not necessary*/
	cltaddr.sin_family = AF_INET;
	cltaddr.sin_port = htons(CLT_PORT);
	cltaddr.sin_addr.s_addr = inet_addr(CLT_ADDR);
	if (-1 == bind(sockfd, (struct sockaddr *)&cltaddr, sizeof(cltaddr)))
		error_exit("bind");
#endif
	
	strcpy(buff, "hellowrold");
	
#if IS_USE_CONNECT
	/* your can use connect on UDP */
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(SER_PORT);
	seraddr.sin_addr.s_addr = inet_addr(SER_ADDR);
	if (-1 == connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("connect");
	
/** then, you can use send/write **/
	if (-1 == send(sockfd, buff, strlen(buff)+1, 0))
		error_exit("send");
	if (-1 == (ret = recv(sockfd, buff, BUFF_SIZE, 0)))
		error_exit("recv");
/*
 * or use write/read
	if (-1 == write(sockfd, buff, strlen(buff)+1))
		error_exit("send");
	if (-1 == (ret = read(sockfd, buff, BUFF_SIZE)))
		error_exit("recv");
*/

#else 
	/* ordinary method */
	if (-1 == sendto(sockfd, buff, strlen(buff)+1, 0,
			(struct sockaddr *)&seraddr, sizeof(seraddr)))
		error_exit("sendto");
	if (-1 == (ret = recvfrom(sockfd, buff, BUFF_SIZE, 0,
					NULL, NULL)))
		error_exit("recvfrom");
#endif
	
	printf("[%d]:%s\n", ret, buff);

	close(sockfd);
	free(buff);

	return 0;
}
