#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

#define BUFF_SIZE	4096
#define ERROR(_ERR_MESG_)	\
	error(EXIT_FAILURE, errno, "%s:%s:%d\n:%s",	\
				__FILE__, __func__, __LINE__, _ERR_MESG_)

int main(int argc, char **argv)
{
	char buff[BUFF_SIZE];
	FILE *destfp = NULL,
		 *srcfp = NULL;

	if (argc != 3)
		ERROR("invalid argment");

	if (NULL == (srcfp = fopen(argv[1], "r"))) 
		ERROR("fopen arv[1]");
	if (NULL == (destfp = fopen(argv[2], "w")))
		ERROR("fopen arv[2]");

	while (NULL != fgets(buff, BUFF_SIZE, srcfp))
		fputs(buff, destfp);

	fclose(srcfp);
	fclose(destfp);
	return 0;
}
