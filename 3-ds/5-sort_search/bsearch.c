#include <stdio.h>
#include <stdlib.h>

int compare(const void *value1, const void *value2)
{
	return *(int *)value1 - *(int *)value2;
}

int main()
{
	int arry[10] = {1,3,5,7,9,2,4,6,8,10};
//	int arry[10] = {1,2,3,4,5,6,7,8,9,10};
	int i;
	int *p = NULL;
	int key;

	for(i = 0; i < 10; i ++)
		printf("%2d ", arry[i]);
	putchar(10);

//	qsort(arry, 10, sizeof(int), compare);
	
	for(i = 0; i < 10; i ++)
		printf("%2d ", arry[i]);
	putchar(10);
	
	for(i = -5; i < 15; i ++)
	{
		key = i + 1;
		p = bsearch(&key, arry, 10, sizeof(int), compare);
		if(p == NULL)
			printf("%d not found !\n", key);
		else
			printf("%2d \n", *p);
	}
	
	return 0;
}

