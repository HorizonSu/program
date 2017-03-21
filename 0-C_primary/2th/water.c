#include <stdio.h>
#define	QUART	950
#define WEIGHT	3.0E-23
int main()
{	
	float n,ret;
	puts("enter your number of quart :");
	scanf("%f",&n);
	ret = QUART * n / WEIGHT;
	printf("the number of water is %e\n",ret);
	return 0;
}
