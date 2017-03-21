#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define	CHAT_COMM_PORT	50000
#define CHAT_COMM_ADDR	"239.0.0.1"

#define CHAT_MESG_LOGIN	'I'
#define CHAT_MESG_LOGOUT 'O'
#define CHAT_MESG_NOMAL	'N'
#define CHAT_MESG_NAME_LEN	32
#define CHAT_MESG_TEXT_LEN	512

typedef struct chat_msg {
	int ch_type;	/* CHAT_LOGIN | CHAT_LOGOUT | CHAT_NOMAL */
	char ch_name[CHAT_MESG_NAME_LEN];
	char ch_text[CHAT_MESG_TEXT_LEN];
}cmsg_t;

#endif /* __PROTOCOL_H__ */
