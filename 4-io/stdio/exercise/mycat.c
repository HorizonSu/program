#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

#define BUFF_SIZE	1024

int main(int argc, char **argv)
{
	char buff[BUFF_SIZE];
	FILE *fp = NULL;
	int lineno = 1;

	if (argc != 2) {
		error(EXIT_FAILURE, errno, "%s:%s:%d\n:invalid argment",
				__FILE__, __func__, __LINE__);
	}

	if (NULL == (fp = fopen(argv[1], "r"))) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fopen\n",
				__FILE__, __func__, __LINE__);
	}

	while (NULL != fgets(buff, BUFF_SIZE, fp))
		fprintf(stdout, "%4d  %s", lineno ++, buff);

	fclose(fp);
	return 0;
}
