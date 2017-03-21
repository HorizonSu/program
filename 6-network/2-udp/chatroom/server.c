#include "server.h"

int pipefd[2];
int sockfd;
linknode_st *userlist = NULL;
mesgpack_st *mesgbuff = NULL;

void sigusr1_handler(int signu)
{
	read(pipefd[0], mesgbuff->data, DATA_BUFF_LEN);
	strcpy(mesgbuff->user, "system");
	broadcast(sockfd, userlist, mesgbuff);
}

int main()
{
	struct sockaddr_in peeraddr;
	socklen_t addrlen;
	pid_t pid;
	
	sockfd = network_init();
	if (-1 == pipe(pipefd))
		error_exit("pipe");
	mesgbuff = (mesgpack_st *)malloc(sizeof(mesgpack_st));
	userlist = (linknode_st *)malloc(sizeof(linknode_st));
	userlist->next = NULL;

	
	if (-1 == (pid = fork()))
		error_exit("fork");
	/* ============== child, process client message ===============*/
	if (0 == pid) {
		close(pipefd[1]);
		signal(SIGUSR1, sigusr1_handler);
		while (1) {
			if( 0 >= recvfrom(sockfd, mesgbuff, sizeof(mesgpack_st),0, 
						(struct sockaddr *)&peeraddr, &addrlen))
				perror("child:recvfrom");
	
			printf("[%d]%s:%d\n", addrlen, 
					inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

			switch (mesgbuff->type) {
			case CMD_CHAT:
				broadcast(sockfd, userlist, mesgbuff);
				break;
			case CMD_LOGIN:
				user_login(sockfd, userlist, (struct sockaddr *)&peeraddr, mesgbuff);
				break;
			case CMD_LOGOUT:
				user_logout(sockfd, userlist, (struct sockaddr *)&peeraddr, mesgbuff);
				break;
			default:
				break;
			}
		}
	} else {
	/* ================ father process local data ============= */
		close(pipefd[0]);
		strcpy(mesgbuff->user, "system");
		setbuf(stdout, NULL);
		
		while (1) {
			printf(">");
			fgets(mesgbuff->data, DATA_BUFF_LEN, stdin);
			write(pipefd[1], mesgbuff->data, DATA_BUFF_LEN);
			kill(pid, SIGUSR1);
		}
	}
	return 0;
}	

int network_init(void)
{
	int sockfd;
	struct sockaddr_in serveraddr;

	if (0 > (sockfd = socket(AF_INET, SOCK_DGRAM, 0)))
		error_exit("socket");

	memset(&serveraddr, 0, sizeof(struct sockaddr));
	
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SER_PORT);
	serveraddr.sin_addr.s_addr = 0;
	
	if (0 > bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)))
		error_exit("bind");

	return sockfd;
}

int _linklist_insert_(linknode_st *userlist, struct sockaddr *addr)
{
	linknode_st *new = NULL;
	
	new = (linknode_st *)malloc(sizeof(linknode_st));
	new->addr = *addr;
	new->next = userlist->next;

	userlist->next = new;
	return 0;
}

int _linklist_delete_(linknode_st * userlist, struct sockaddr *peeraddr)
{
	linknode_st *tmp = NULL;

	if (userlist == NULL || peeraddr == NULL)
		return -1;
	
	while (NULL != userlist->next) {
		if (0 == memcmp(userlist->next, peeraddr, sizeof(struct sockaddr))) {
			tmp = userlist->next;
			userlist->next = tmp->next;
			free(tmp);
		}
		userlist = userlist->next;
	}
	return 0;
}

int user_login(int sockfd, linknode_st *userlist, struct sockaddr *peeraddr, mesgpack_st *mesgbuff)
{
	_linklist_insert_(userlist, peeraddr);
	
	mesgbuff->type = CMD_CHAT;
	sprintf(mesgbuff->data, "%s login !\n", mesgbuff->user);
	strcpy(mesgbuff->user, "system");

	broadcast(sockfd, userlist, mesgbuff);
	return 0;
}

int user_logout(int sockfd, linknode_st *userlist, struct sockaddr *peeraddr, mesgpack_st *mesgbuff)
{

	_linklist_delete_(userlist, peeraddr);

	mesgbuff->type = CMD_CHAT;
	sprintf(mesgbuff->data, "%s logout !\n", mesgbuff->user);
	strcpy(mesgbuff->user, "system");
	
	broadcast(sockfd, userlist, mesgbuff);
	return 0;
}

int broadcast(int sockfd, linknode_st *userlist, mesgpack_st *mesgbuff)
{
	int mesglen;

	mesglen = offsetof(mesgpack_st, data) + strlen(mesgbuff->data) + 1;

	while(NULL != userlist->next) {
		if( 0 >= sendto(sockfd, mesgbuff, mesglen, 0, &userlist->next->addr, sizeof(struct sockaddr)))
			perror("broadcast:sendto");
		userlist = userlist->next;
	}
	return 0;
}
