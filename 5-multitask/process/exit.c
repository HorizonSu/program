# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

int main()
{
	printf("test the exit ... ...");
# if 0
	exit(EXIT_SUCCESS);
# else
	_exit(EXIT_SUCCESS);
# endif

	return 0;
}
