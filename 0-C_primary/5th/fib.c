#include <stdio.h>
#define N 20

int main()
{
	int i;
	int a[N] = {1,1};
	for(i = 2; i < N; i ++)
		a[i] = a[i -1] + a[i - 2];

	for(i = N - 1; i >= 0; i --)
		printf("%d\t",a[i]);
	putchar(10);
	return 0;
}
	
