#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

#define ERROR(_errmesg_)	error(EXIT_FAILURE, errno, "%s:%d->%s\n", \
		__FILE__, __LINE__, _errmesg_)

#define BLOCKSIZE	1 << 20
#define BUFFSIZE	BLOCKSIZE
#define NAMELEN		256

int main(int argc, char *argv[])
{
	int blocksize = BLOCKSIZE;
	char *filename = NULL;
	FILE *srcfp = NULL,
		 *destfp = NULL;
	char *blockbuff = NULL,
		 *namebuff = NULL;
	int fileno = 0;
	int nbytes;

	if (argc != 2)
		ERROR("invalid argument");
	filename = argv[1];
	
	blockbuff = (char *)malloc(BUFFSIZE);
	namebuff = (char *)malloc(NAMELEN);
	
	if (NULL == (destfp = fopen(filename, "w+")))
		ERROR(filename);

	while (1) {
		sprintf(namebuff, "%s.[%d]", filename, fileno ++);
		if (NULL == (srcfp = fopen(namebuff, "r")))
			break;
		while (0 != (nbytes = (fread(blockbuff, 1, BLOCKSIZE, srcfp)))) {
			if ( 0 == fwrite(blockbuff, nbytes, 1, destfp))
				ERROR("fwrite");
		}
		fclose(srcfp);
	}

	free(blockbuff);
	free(namebuff);
	fclose(destfp);
	
	return 0;
}
