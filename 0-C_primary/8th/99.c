#include <stdio.h>

int main()
{
	int a[9][9] = {0};
	int i,j;

	for(i = 0; i < 9; i ++)
	{
		for(j = 0;j <= i; j ++)
			a[i][j] = (i + 1) * (j + 1);
	}
	
	for(i = 0; i < 9; i ++)
	{
		for(j = 0;j <= i; j ++)
			printf("%4d",a[i][j]);
		putchar(10);
	}
	puts("-----------------------");
	for(i = 8; i >= 0; i --)
	{
		for(j = i; j >= 0;j --)
			printf("%4d",a[i][j]);
		putchar(10);
	}

	return 0;
}
