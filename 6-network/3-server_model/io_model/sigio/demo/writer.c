#include "head.h"

int main()
{
	int fifd;
	char buff[BUFF_SIZE];
	
	if (-1 == mkfifo(FIFO_PATH, 0666)) {
		if (EEXIST != errno)
			error_exit("mkfifo");
	}

	if (-1 == (fifd = open(FIFO_PATH, O_WRONLY)))
		error_exit("open");

	while (1) {
		puts(">");
		fgets(buff, BUFF_SIZE, stdin);
		if (-1 == write(fifd, buff, strlen(buff)+1))
			error_exit("write");
	}

	return 0;
}
