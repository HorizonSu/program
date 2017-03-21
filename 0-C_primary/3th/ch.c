#include <stdio.h>

int main()
{
	char ch;
	puts("input one charactor:");
	ch = getchar();
#if 0
	if(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
		putchar(ch > 'Z' ? ch - 32 : ch + 32);
#endif

#if 1
	if(ch >= '0' && ch <= '9')
		puts("it`s a number !");
	else if(ch >= 'A' && ch <= 'Z')
	{
		putchar(ch + 32);
		putchar(10);
	}
	else if(ch >= 'a' && ch <= 'z')
	{
		putchar(ch - 32);
		putchar(10);
	}
	else
		puts("error !");
#endif
	return 0;
}
