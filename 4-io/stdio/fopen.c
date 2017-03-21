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

#if 0
	if (NULL == (fp = fopen(FILE_PATH, "r"))) {
		perror("fopen:");
		exit(EXIT_FAILURE);
	}
#else
	if (NULL == (fp = fopen(FILE_PATH, "w"))) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fopen %s\n",
				__FILE__, __func__, __LINE__ - 1, FILE_PATH);
	}
#if 0

	if ( EOF == fputs(buff, fp)) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fputs\n",
				__FILE__, __func__, __LINE__ - 1);
	}

	if (NULL == fgets(buff, BUFF_SIZE, fp) && ! feof(fp)) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fgets\n",
				__FILE__, __func__, __LINE__ - 1);		
	}
#endif
	puts(buff);

#endif

	fclose(fp);
	return 0;
}
