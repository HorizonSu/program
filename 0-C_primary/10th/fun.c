#include <stdio.h>
#define N 20
#define MAX(X,Y) (			\
{					        \
     const typeof(X) _x = (X);           \
     const typeof(Y) _y = (Y);           \
		(void)(&_x == &_y);				\
	(_x) > (_y) ? (_x) : (_y);	\
})

int x = 10;
char y = 15;
int main()
{
	 int * z;
	 z = MAX(&y,&x);
#if 0
	z = ({
		int x  =100;
		int y = 200;
		x > y ? x : y;
	});
#endif
	 printf("the max = %p\n",z);
	 return 0;
}
