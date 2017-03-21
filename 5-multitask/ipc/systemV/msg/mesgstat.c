#include "head.h"

int main()
{
	key_t key;
	int msgid;
	struct msqid_ds msgstat;
	struct msgbuf {
		int type;
		char buff[BUFF_SIZE];
	}msgbuf;

	key = ftok(KEY_FILE, KEY_MAGIC);

	if (-1 == (msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0644)))
		ERROR("msgget");
	
	msgbuf.type = 1;
	strcpy(msgbuf.buff, "helloworld");
	if (-1 == msgsnd(msgid, &msgbuf, BUFF_SIZE, 0))
		ERROR("msgsnd");

	if (-1 == msgctl(msgid, IPC_STAT, &msgstat))
		ERROR("msgctl.IPC_STAT");

	printf("current bytes: %d\n", msgstat.__msg_cbytes);
	printf("current qnumber: %d\n", msgstat.msg_qnum);
	printf("maxbytes: %d\n", msgstat.msg_qbytes);
	printf("key: %#x\n", msgstat.msg_perm.__key);
	printf("seq: %d\n", msgstat.msg_perm.__seq);

	return 0;
}
