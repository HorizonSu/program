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
	FILE *oldfp = NULL,
		 *newfp = NULL;
	char *blockbuff = NULL,
		 *namebuff = NULL;
	int fileno = 0;
	int nbytes;

	if (argc != 2)
		ERROR("invalid argument");
	filename = argv[1];
	
	blockbuff = (char *)malloc(BUFFSIZE);
	namebuff = (char *)malloc(NAMELEN);
	
	if (NULL == (oldfp = fopen(filename, "r")))
		ERROR(filename);
	
	while (0 != (nbytes = fread(blockbuff, 1, BLOCKSIZE, oldfp))) {
		sprintf(namebuff, "%s.[%d]", filename, fileno ++);
		if (NULL == (newfp = fopen(namebuff, "w")))
			ERROR(namebuff);
		if ( 0 == fwrite(blockbuff, nbytes, 1, newfp))
			ERROR("fwrite");
		fclose(newfp);
	}
	if (!feof(oldfp))
		ERROR("fread");

	free(blockbuff);
	free(namebuff);
	fclose(oldfp);
	
	return 0;
}
