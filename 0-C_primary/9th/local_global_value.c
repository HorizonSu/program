#include <stdio.h>

int add_p(int *,int *);
int add(int ,int);
int add_global(void);

int x = 100,y = 300;

int main()
{
#if 1
	int x = 10,
		y = 20;
	int z;
	int *px = &x,
		*py = &y;
	
	z = add_global();
	printf("add_global = %d\n",z);
	z = add_p(px,py);
	printf("add_p = %d\n",z);
	z = add(x,y);
	printf("add = %d\n",z);
#endif
}

int add_global(void)
{
	return x + y;
}

#if 1

int add_p(int *pa,int *pb)
{
//	printf("add_p  :&pa = %p\n&pb = %p\n",&pa,&pb);
	return *pa + *pb;
}

int add(int a,int b)
{
//	printf("add :x = %p\ny = %p\n",&a,&b);
	return a + b;
}

#endif
