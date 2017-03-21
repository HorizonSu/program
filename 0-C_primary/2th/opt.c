#include <stdio.h>

int main()
{
	int x = 0,y = 0;
	puts("enter two number:");
	scanf("%d%d",&x,&y);
	printf("x + y = %d\n",x + y);
	printf("x - y = %d\n",x - y);
	printf("x * y = %d\n",x * y);
	printf("x / y = %d\n",x / y);
	printf("x %% y = %d\n",x % y);
	printf("x / y = %f\n",x / (float)y);
	return 0;
}
