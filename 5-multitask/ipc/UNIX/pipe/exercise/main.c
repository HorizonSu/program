#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <express.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

int main()
{
	pid_t pid;
	FILE *fp = NULL;
	char *buff = NULL;
	int result;

	if (NULL == (fp = tmpfile()))
		ERROR_EXIT("tmpfile");

	buff = (char *)malloc(BUFF_SIZE);

	if (-1 == (pid = fork()))
		ERROR_EXIT("fork");
	
	if (0 == pid) {
		/*  father  */
		strcpy(buff, "2+3*4-1");
		if (0 >= fputs(buff, fp))
			ERROR_EXIT("fputs");
	} else {
		/*  child */
		sleep(1);
		rewind(fp);
		if (NULL == fgets(buff, BUFF_SIZE, fp))
			ERROR_EXIT("fgets");
		result = express(buff);

		printf("%s = %d\n", buff, result);
	}

	return 0;
}
