#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

#ifndef FILE_PATH
#define FILE_PATH	"./testfile.txt"
#endif
#define BUFF_SIZE	4096


int main()
{
	FILE *fp = NULL;
	char buff[BUFF_SIZE] = "helloworld\n";

	if (NULL == (fp = fopen(FILE_PATH, "w"))) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fopen %s\n",
				__FILE__, __func__, __LINE__ - 1, FILE_PATH);
	}

	if ( EOF == fputs(buff, fp)) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fputs\n",
				__FILE__, __func__, __LINE__ - 1);
	}
	fseek(fp, 2048, SEEK_SET);
	if ( EOF == fputs(buff, fp)) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fputs\n",
				__FILE__, __func__, __LINE__ - 1);
	}

	fseek(fp, 1024, SEEK_SET);

	if ( EOF == fputs(buff, fp)) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fputs\n",
				__FILE__, __func__, __LINE__ - 1);
	}
	


	fclose(fp);
	return 0;
}
