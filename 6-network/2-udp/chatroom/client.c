#include "head.h"

int main()
{
	int sockfd;
	struct sockaddr_in serveraddr;
	pid_t pid;
	mesgpack_st *mesgbuff = NULL;
	int len;
	time_t time_sec;
	
	mesgbuff = (mesgpack_st *)malloc(sizeof(mesgpack_st));

	/* =================== network init =================== */
	if( 0 > (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		error_exit("socket");
	
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SER_PORT);
	serveraddr.sin_addr.s_addr = inet_addr(SER_ADDR);

	if( 0 > connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)))
		error_exit("connect");

	/* ================= user login ===================*/
	puts("enter your name:");
	/* read user name */
	fgets(mesgbuff->user, USER_NAME_LEN, stdin);
	mesgbuff->user[strlen(mesgbuff->user)-1] = 0;
	mesgbuff->type = CMD_LOGIN;

	if (0 > send(sockfd, mesgbuff, offsetof(mesgpack_st, data), 0))
		error_exit("register");

	if (-1 == (pid = fork()))
		error_exit("fork");
	/* ==================== father process, send message ================ */
	if (pid > 0)	{
		while (1) {
			/* read local messaga */
			fgets(mesgbuff->data, DATA_BUFF_LEN, stdin);
			/* quit */
			if (0 == strcmp(mesgbuff->data, "#quit\n"))	{	
				mesgbuff->type = CMD_LOGOUT;
				if( 0 > send(sockfd, mesgbuff, offsetof(mesgpack_st, data), 0))
					perror("quit:send");
				sleep(1);
				kill(pid, SIGKILL);
				exit(EXIT_SUCCESS);
			}

			mesgbuff->type = CMD_CHAT;
			len = offsetof(mesgpack_st,data) + strlen(mesgbuff->data) + 1;
			if (0 > send(sockfd, mesgbuff, len, 0))
				perror("chat:send");
		}
	} else {
	/* ====================== child process, receive message ====================*/
		while (1) {
			time_sec = time(NULL);
			if (0 > recv(sockfd, mesgbuff, sizeof(mesgpack_st), 0))
				perror("child:recv");
			printf("\e[1;31m%s\e[0m\e[1;33m#\e[0m\t\e[1;32m%s\e[0m%s",
					mesgbuff->user, ctime(&time_sec), mesgbuff->data);
		}
	}
	free(mesgbuff);
	return 0;
}
