#include "home_head.h"

int main(int argc, const char **argv)
{
	struct _msq_info_ msginfo;
	int cmd;
	int opt;
	int value;
	int msgid;

	if (4 != argc) {
		puts("invalid argument");
		return 0;
	}
	
	cmd = argv[1][0];
	opt = argv[2][0];
	if (opt != OPT_ON && opt != OPT_OFF) {
		printf("invalid operation '%c'\n", opt);
		return 0;	
	}
	value = atoi(argv[3]);

	if (-1 == (msgid = msgget(IPC_KEY, IPC_CREAT | 0666)))
		error_exit("msgget");

	msginfo.mtype = SMSG_CGI_TYPE;
	msginfo.mctl.c_type = cmd;
	msginfo.mctl.c_opt = opt;
	msginfo.mctl.c_value = value;

	switch (cmd) {
	case CMD_KONGTIAO:
	case CMD_RESHUI:
	case CMD_DENG:
		if (-1 == msgsnd(msgid, &msginfo, sizeof(msginfo)-sizeof(long), 0))
			error_exit("msgsnd");
		break;
	default:
		puts("cmd error !");
		return -1;
	}

	return 0;
}
