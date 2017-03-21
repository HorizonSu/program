#include <stdio.h>

int main()
{
	char ch,i,j;
	puts("input your charactor :");
	ch = getchar();
	if(ch >= 'A' && ch <= 'Z');
	else if(ch >= 'a' && ch <= 'z')
		ch -= 32;
	else
	{
		puts("data error !");
		return -1;
	}

#if 0
	for(i = 0; i <= ch - 'A'; i ++)
	{
		for(j = 0; j < i ; j ++)
			putchar('_');
		for(j = 0; j <= i; j ++)
			putchar(ch - j);
		putchar(10);
	}
#else
	for(i = 1; i <= ch - 'A' + 1; i ++)
	{
		for(j = 0; j <= 2*i -1; j ++)
		{
			if(j < i)
				putchar('_');
			else
				putchar(ch - j + i);
		}
		putchar(10);
	}
#endif
	return 0;
}
