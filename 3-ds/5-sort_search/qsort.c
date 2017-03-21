#include <stdio.h>
#include <stdlib.h>

int compare(const void *value1, const void *value2)
{
	return *(int *)value1 - *(int *)value2;
}

int main()
{
	int arry[10] = {1,3,5,7,5,2,4,6,8,10};
	int i;

	for(i = 0; i < 10; i ++)
		printf("%2d ", arry[i]);
	putchar(10);
	
	qsort(arry,10,sizeof(int), compare);

	for(i = 0; i < 10; i ++)
		printf("%2d ", arry[i]);
	putchar(10);
	
	return 0;
}
