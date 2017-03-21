#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

#define BUFF_SIZE	4096

int main()
{
	FILE *fp = NULL;
	char buff[BUFF_SIZE] = "helloworld\n";
	char *filename = NULL;

#if 1

	filename = tmpnam(NULL);
	puts(filename);
	if (NULL == (fp = fopen(filename, "w"))) {
		error(EXIT_FAILURE, errno, "%s:%s:%d->fopen %s\n",
				__FILE__, __func__, __LINE__ - 1, filename);
	}
#else
	fp = tmpfile();
#endif

	fputs("ilovechina 1234567890", fp);
	rewind(fp);
	fgets(buff, BUFF_SIZE, fp);

	puts(buff);

	fclose(fp);
	remove(filename);
	return 0;
}
