#include <stdio.h>

int main()
{
	int num,i,sum;
	for(num = 1; num <= 1000; num ++)
	{
		sum = 0;
		for(i = 1; i < num; i ++)
		{
			if(!(num % i))
				sum += i;
		}
		if(sum == num)
			printf("%d\n",num);
	}
	return 0;
}
