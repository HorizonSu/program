#include <stdio.h>
int main()
{
	int x,y,tmp;
	puts("enter your number:");
	scanf("%d%d",&x,&y);
#if 0
	tmp = x;
	x = y;
	y = tmp  y;
//#else
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
#endif
	x = x - y;
	y = x + y;
	x = y - x;

	printf("x = %d\ty = %d\n",x,y);
	return 0;
} 
