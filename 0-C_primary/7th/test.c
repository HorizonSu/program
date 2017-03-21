#include <stdio.h>
#define N 30

int main()
{
	char a[N] = {0},
		 b[N] = {0},
		 c[N] = {0};
	char ch = 0;
	int an = 0,
		bn = 0,
		cn = 0;
	int i,j;

	puts("input your string:");
	while(an + bn + cn < N && '#' != (ch = getchar()))
	{
		if(ch <= 32)
			continue;
		if(ch >= 'A' && ch <= 'Z')
			a[an ++] = ch;
		else if(ch >= 'a' && ch <= 'z')
			a[an ++] = ch - 32;
		else if(ch >= '0' && ch <= '9')
			b[bn ++] = ch;
		else
			c[cn ++] = ch;
	}

	for(i = 0; i < bn - 1; i ++)
	{
		for(j = 0; j < bn - i - 1; j ++)
		{
			if(b[j] > b[j + 1])
			{
				b[j] ^= b[j + 1];
				b[j + 1] ^= b[j];
				b[j] ^= b[j + 1];
			}
		}
	}
	i = 0;
	j = an -1;
	while(i < j)
	{
		a[i] ^= a[j];
		a[j] ^= a[i];
		a[i ++ ] ^= a[j --];
	}
	printf("length:\t%d\tstring:\t%s\n",an,a);
	printf("length:\t%d\tstring:\t%s\n",bn,b);
	printf("length:\t%d\tstring:\t%s\n",cn,c);
	return 0;
}
