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
	int nbyte = 0;

	if (argc != 3)
		ERROR("invalid argment");

	if (NULL == (srcfp = fopen(argv[1], "r"))) 
		ERROR("fopen arv[1]");
	if (NULL == (destfp = fopen(argv[2], "w")))
		ERROR("fopen arv[2]");

	while (0 != (nbyte = fread(buff, 1, BUFF_SIZE, srcfp))) {
		if (0 == fwrite(buff, 1, nbyte, destfp))
			break;
	}

	fclose(srcfp);
	fclose(destfp);
	return 0;
}
