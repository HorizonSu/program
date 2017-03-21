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
	int nbyte = 0;

	if (NULL == (fp = fopen(FILE_PATH, "w+"))) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fopen %s\n",
				__FILE__, __func__, __LINE__ - 1, FILE_PATH);
	}

	if (0  == (nbyte = fwrite(buff, 1, BUFF_SIZE, fp))) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fputs\n",
				__FILE__, __func__, __LINE__ - 1);
	}
	printf("writen: %d\n", nbyte);

	fseek(fp, 0, SEEK_SET);
	buff[0] = 0;

#if 1
	if (0 == (nbyte = fread(buff, 1, BUFF_SIZE, fp))) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fgets\n",
				__FILE__, __func__, __LINE__ - 1);		
	}
	printf("read: %d\n", nbyte);
	puts(buff);
#endif
	fclose(fp);
	return 0;
}
