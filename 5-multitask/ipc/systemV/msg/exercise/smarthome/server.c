#include "home_head.h"

int main()
{
	int msgid;
	struct _msq_info_ msginfo;
	int opt;
	int value;

	/* system init */
	if (-1 == (msgid = msgget(IPC_KEY, IPC_CREAT | 0666)))
		error_exit("msgget");

	while (1) {
		if (-1 == msgrcv(msgid, &msginfo, sizeof(msginfo)-sizeof(long), SMSG_CGI_TYPE, 0))
			error_exit("msgsnd");
		opt = msginfo.mctl.c_opt;
		value = msginfo.mctl.c_value;

		switch (msginfo.mctl.c_type) {
		case CMD_KONGTIAO:
			if (opt == OPT_ON)
				printf("kongtiao ----- [%d]  ------- ON \n", value);
			else
				printf("kongtiao ----- ---  ------- OFF\n");
			break;
		case CMD_RESHUI:
			if (opt == OPT_ON)
				printf("reshui ----- [%d]  ------- ON \n", value);
			else
				printf("reshui ----- ----- ------- OFF \n");
			break;
		case CMD_DENG:
			if (opt == OPT_ON)
				puts("deng ----------------- ON");
			else
				puts("deng ----------------- OFF");
			break;
		default:
			puts("cmd error !");
		}

	}
	return 0;
}
