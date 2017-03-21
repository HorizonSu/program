#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

#define BUFF_SIZE	1024

int main(int argc, char **argv)
{
	char buff[BUFF_SIZE];
	FILE *fp = NULL;

	if (argc != 2) {
		error(EXIT_FAILURE, errno, "%s:%s:%d\n:invalid argment",
				__FILE__, __func__, __LINE__);
	}

#if 1
	if (NULL == (fp = fopen(argv[1], "w"))) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fopen\n",
				__FILE__, __func__, __LINE__);
	}

	fgets(buff, BUFF_SIZE, stdin);
	if (EOF == fputs(buff, fp)) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fputs\n",
				__FILE__, __func__, __LINE__);
	}

	fclose(fp);
#endif
	return 0;
}
