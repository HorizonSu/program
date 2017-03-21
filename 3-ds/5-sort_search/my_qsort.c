#include <stdio.h>
//#include <stdlib.h>

int myqsort(int *arry, int low, int high);

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
	
//	myqsort(arry,10,sizeof(int), compare);
	myqsort(arry,0, 10 - 1);

	for(i = 0; i < 10; i ++)
		printf("%2d ", arry[i]);
	putchar(10);
	
	return 0;
}

#if 1

void swap(int *value1, int *value2)
{
	int tmp;
	if(value1 == value2)
		return ;
#if 0	
	tmp = *value1;
	*value1 = *value2;
	*value2 = tmp;
#else
	*value1 ^= *value2;
	*value2 ^= *value1;
	*value1 ^= *value2;
#endif
}

int partition(int arry[], int low, int high)
{
	int key = arry[low];

	while(low < high)
	{
		while(low < high && arry[high] >= key)
			high --;
		swap(arry+high, arry+low);

		while(low < high && arry[low] <= key)
			low ++;
		swap(arry+high, arry+low);
	}
	return low;
}

int myqsort(int *arry, int low, int high)
{
	int pivottag;

	if(low >= high)
		return 0;
	
	pivottag = partition(arry, low, high);
	myqsort(arry, low, pivottag-1);
	myqsort(arry, pivottag+1, high);

	return 0;
}
#endif
