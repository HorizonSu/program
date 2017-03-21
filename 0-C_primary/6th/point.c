#include <stdio.h>
int c;

int main()
{	
	int  a[10] = {1,2,3,4,5,6,7,8,9};
	int *p = a;
	while(p - a < 10)
		printf("%d\n",*p ++);
	return 0;
}
