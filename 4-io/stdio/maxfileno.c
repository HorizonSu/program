#include <stdio.h>

#define FILEPATH	"/tmp/test.txt"

int main()
{
	int counter;
	FILE *fp = NULL;

	for (counter = 0; ;counter ++)
	{
		if ( NULL == (fp = fopen(FILEPATH, "w")))
			break;
	}
	printf("counter: %d\n", counter);
	
	unlink(FILEPATH);
	return 0;
}
