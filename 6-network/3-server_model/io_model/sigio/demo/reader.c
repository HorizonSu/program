#include "head.h"

int fifd;
char buff[BUFF_SIZE];
void sigio_handler(int sigio);

int main()
{
	long flag;
	
	if (SIG_ERR == signal(SIGIO, sigio_handler))
		error_exit("signal");

	
	if (-1 == mkfifo(FIFO_PATH, 0666)) {
		if (EEXIST != errno)
			error_exit("mkfifo");
	}

	if (-1 == (fifd = open(FIFO_PATH, O_RDONLY)))
		error_exit("open");
	
	flag = fcntl(fifd, F_GETFL);
	fcntl(fifd, F_SETFL, flag | O_ASYNC);
	fcntl(fifd, F_SETOWN, getpid());

	while (1) {
		sleep(1);
		if (-1 == system("date"))
			error_exit("system");
	}

	return 0;
}

void sigio_handler(int sigio)
{
	if (-1 == read(fifd, buff, BUFF_SIZE))
		error_exit("write");
	printf("<%s", buff);
	
	return;
}
