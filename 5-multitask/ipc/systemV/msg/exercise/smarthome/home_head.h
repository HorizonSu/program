#ifndef __HOME_HEAD_H__
#define __HOME_HEAD_H__

#include <head.h>

#define IPC_KEY		0X01020304
#define SMSG_CGI_TYPE	'C'

#define CMD_KONGTIAO	'k'
#define CMD_RESHUI		'r'
#define CMD_DENG		'd'

#define	OPT_ON	'1'
#define OPT_OFF	'0'

struct _ctl_info_ {
	int c_type;
	int c_opt;
	int c_value;
};

struct _msq_info_ {
	long mtype;
	struct _ctl_info_ mctl;
};

#endif /* __HOME_HEAD_H__ */
