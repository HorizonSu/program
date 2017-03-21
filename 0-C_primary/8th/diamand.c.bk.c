#include <stdio.h>

int main()
{
	int i,j;
	int nu;
	puts("input your number:");
	while(1 != scanf("%d",&nu))
		getchar();
	
	for(i = 0; i < nu; i ++)
	{
		for(j = nu - i; j > 0; j --)
			putchar('.');
		for(j = 0; j < 2 * i + 1; j ++)
			putchar('*');
		for(j = nu - i; j > 0; j --)
			putchar('.');
		putchar(10);
	}
	for(i = 0; i < nu -1; i ++ )
	{
		for(j = 0;j < i + 2; j ++ )
			putchar('.');
		for(j = 2 * (nu - i) - 3; j > 0; j -- )
			putchar('*');
		for(j = 0;j < i + 2; j ++ )
			putchar('.');
		putchar(10);
	}
	return 0;
}

