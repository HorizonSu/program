#ifndef __SERVER_H__
#define __SERVER_H__

#include "head.h"


typedef struct _linknode_{
	struct sockaddr addr;
	struct _linknode_ *next;
}linknode_st;

extern int _linklist_insert_(
		linknode_st *userlist, 
		struct sockaddr *addr);
extern int _linklist_delete_(
		linknode_st * userlist, 
		struct sockaddr *peeraddr);

extern int broadcast(
		int sockfd, 
		linknode_st *userlist, 
		mesgpack_st *mesgbuff);
extern int user_logout(
		int sockfd, 
		linknode_st *userlist, 
		struct sockaddr *peeraddr,
		mesgpack_st *mesgbuff);
extern int user_login(
		int sockfd, 
		linknode_st *userlist, 
		struct sockaddr *peeraddr, 
		mesgpack_st *mesgbuff);
extern int network_init(void);

#endif
