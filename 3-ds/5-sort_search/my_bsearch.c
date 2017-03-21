#include <stdio.h>
//#include <stdlib.h>

int *bsearch(int *arry, int size, int obj)
{
	int low = 0,
		high = size - 1,
		mid = 0;
#if 0
	if(arry[low] == obj)
		return arry;
	if(arry[high] == obj)
		return arry + high;
#endif

	while(low <= high)
	{
	//	mid = (high + low) / 2;
		mid = (high - low) / 2 + low;
		
		if(arry[mid] == obj)
			return arry + mid;
		if(arry[mid] < obj)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return NULL;
}

int main()
{
	int arry[10] = {1,2,3,4,5,6,7,8,9,10};
	int i;
	int *ret;


	for(i = 0; i < 10; i ++)
		printf("%2d ", arry[i]);
	putchar(10);
	
	for(i = 0; i < 15; i ++)
	{
	ret = bsearch(arry, 10, i);	
	if(ret == NULL)
		printf("%d not found !\n", i);
	else
		printf("%2d\n", *ret);
	}
	return 0;
}

