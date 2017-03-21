#include <stdio.h>
int main()
{
	int i = 0,year;
	for(year = 1; year <= 2012; year ++)
	{
		if(!(year % 4) && (year % 100) || !(year % 400))
		{
			printf("%6d",year);
			if(!( ++ i % 10 ))
				putchar(10);
		}
#if 0
		if(!(i % 4))
		{
			if(i % 100)
				printf("%6d",i);
			else if (!(i % 400))
				printf("%6d",i);
		}
#endif
	}
	putchar(10);
	return 0;
}
