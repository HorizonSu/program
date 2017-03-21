#include <stdio.h>

int main()
{
	char ch = 'F';
	ch = getchar();
	int i,j;
	for(i = 0; i <= ch - 'A'; i ++)
	{
		for(j = 0; j < i ; j ++)
			putchar('_');
#if 1
		for(j = 0; j <= i; j ++)
			putchar(ch - j);
#endif
		putchar(10);
	}
	return 0;
}
