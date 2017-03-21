#include <stdio.h>
#include <stdlib.h>

int value;

int main()
{
	char str[] = "jflsdkfjs";
	
#if 1
	printf(".text:\t%p\n", main);
	printf(".roda:\t%p\n", "helloworld");
	printf(".data:\t%p\n", &value);
	printf("HEAP:\t%p\n", malloc(10));
	printf("STACK:\t%p\n", str);
#endif

	return 0;
}
