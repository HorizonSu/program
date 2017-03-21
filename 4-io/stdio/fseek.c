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

	if (NULL == (fp = fopen(FILE_PATH, "w+"))) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fopen %s\n",
				__FILE__, __func__, __LINE__ - 1, FILE_PATH);
	}

	if ( EOF == fputs(buff, fp)) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fputs\n",
				__FILE__, __func__, __LINE__ - 1);
	}
	
	if ( EOF == fputs(buff, fp)) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fputs\n",
				__FILE__, __func__, __LINE__ - 1);
	}
#if 0
	fseek(fp, 11, SEEK_SET);
//#else
	fseek(fp, -11, SEEK_CUR);
#endif
	fseek(fp, 0, SEEK_SET);
	buff[0] = 0;
	
#if 0
	if (NULL == fgets(buff, BUFF_SIZE, fp) && ! feof(fp)) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fgets\n",
				__FILE__, __func__, __LINE__ - 1);		
	}
#endif
	while( NULL != fgets(buff, BUFF_SIZE, fp))
		fputs(buff, stdout);

	printf("offset: %d\n", ftell(fp));
	
	fclose(fp);
	return 0;
}
