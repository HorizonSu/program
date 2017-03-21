#include <stdio.h>

void fun(int x);
void (*fun2(int x,void(*)(int)))(int);

int main()
{
	void(*p)(int) = NULL;
	void (*(*funp)(int x,void(*)(int)))(int) = fun2;
	int x = 10;
	p = funp(x,fun);
	p(x);
	return 0;
}

void fun(int x)
{
	printf("2x = %d\n",2 * x);

}
void (*fun2(int x,void(*funp)(int)))(int)
{
	printf("x = %d\n",x);
	funp(x);
	return funp;
}
