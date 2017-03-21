#include <stdio.h>

int main()
{
	int a[] = {2,3,6,7,10};
	int b[] = {1,4,5,8,9};
	int c[10];
	int index_a = 0,
		index_b = 0,
		index_c = 0;

	for (; index_a < 5 && index_b < 5; index_c ++) {
		if(a[index_a] < b[index_b])
			c[index_c] = a[index_a ++];
		else
			c[index_c] = b[index_b ++];
	}
	
	if (index_a < 5)
		c[index_c] = a[index_a];
	else
		c[index_c] = b[index_b];

	for (index_a = 0; index_a < 10; index_a ++)
		printf("%3d",c[index_a]);
	putchar(10);

	return 0;
}
