#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <error.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define KEY_VALUE	0X01020304
#define MSG_SIZE	1024
#define MSG_TYPE1	'1'
#define MSG_TYPE2	'2'

typedef struct _mesg_buff_{
	long type;
	char info[MSG_SIZE];
}msgbuf_st;

int main()
{
	int msgid;
	pid_t pid;
	msgbuf_st *msgbuf = NULL;
	
	msgbuf = (msgbuf_st *)malloc(sizeof(msgbuf_st));
	
	if (-1 == (msgid = msgget(KEY_VALUE, IPC_CREAT | 0777)))
		ERROR_EXIT("msgget");

	if (-1 == (pid = fork()))
		ERROR_EXIT("fork");

	if (0 == pid) {	
		/*child, receive mesg*/
		while (1) {
			memset(msgbuf->info, 0, MSG_SIZE);
			if (-1 == msgrcv(msgid, msgbuf, sizeof(msgbuf->info), MSG_TYPE2, 0))
				ERROR_EXIT("msgrcv");
			fputs(msgbuf->info, stdout);
		}
		
	}else {
		/*father , send mesg*/
		while (1) {
			fgets(msgbuf->info, MSG_SIZE, stdin);
			msgbuf->type = MSG_TYPE1;
			if (-1 == msgsnd(msgid, msgbuf, strlen(msgbuf->info), 0))
				ERROR_EXIT("msgsnd");
			if (!strcmp("#quit\n", msgbuf->info))
				break;
		}
	}

	kill(pid, SIGKILL);
	free(msgbuf);
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
	
