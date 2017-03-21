#include <stdio.h>
#define N 10
int main()
{
	int a[N] = {10,9,8,7,6,5,4,3,2,1};
	int i,j;

	for(i = 0; i < N; i ++)
	{
		while(!scanf("%d",&a[i]))
			getchar();
	}

	for(i = 0; i < N - 1; i ++)
	{
		for(j = 0; j < N - i - 1 ; j ++)
		{
			if(a[j] > a[j + 1])
			{
				a[j] ^= a[j + 1];
				a[j + 1] ^= a[j];
				a[j] ^= a[j + 1];
			}
		}
	}

	for(i = 0; i < N; i ++)
		printf("%d\t",a[i]);
	putchar(10);
	return 0;
}
