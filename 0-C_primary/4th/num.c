#include <stdio.h>
#include <math.h>


int main()
{
	int num,i;
	for(num = 2; num <= 100; num ++)
	{
		for(i = 2; i < sqrt(num); i ++)
		{
			if(!(num % i))
				break;
		}
		if(i > sqrt(num))
			printf("%5d",num);
	}
	return 0;
}
