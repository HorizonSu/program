#include <stdio.h>

void(*fun1(int, void(*y)(int)))(int);
void fun(int nu);

int main()
{
	void(*(*p)(int, void(*)(int)))(int) = fun1;
	p(100,fun);

}

void fun(int nu)
{
	printf("fun : %d\n",nu);
}

void(*fun1(int nu, void(*fun_p)(int)))(int)
{
	fun_p(nu);
	return fun_p;
}


