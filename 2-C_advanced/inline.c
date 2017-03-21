#include <stdio.h>
#define DEBUG 0
#define ADD(X,Y) ((X) + (Y))	
#if DEBUG

__attribute__((always_inline))
inline int add(int x, int y) 
{
	return x + y;
}

#endif
int main()
{
	int x = 10,
		y = 20;
	int z = 0;
	volatile int i;
	for (i = 0; i < 1000000000; i ++)
#if DEBUG
		z = add(x,y);
#else
		z = ADD(x,y);
#endif
	printf("%d\n",z);
	return 0;
}

