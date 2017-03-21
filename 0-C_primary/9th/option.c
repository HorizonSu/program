#include <stdio.h>

int add(int,int);
int sub(int,int);
int mul(int,int);
float div(int,int);
int *get_data(int *);

int main()
{
	int x = 10,
		y = 20;
	int a[2];
	get_data(a);
	
	x = a[0];
	y = a[1];

	printf("%d + %d = %d\n",x,y,add(x,y));
	printf("%d - %d = %d\n",x,y,sub(x,y));
	printf("%d * %d = %d\n",x,y,mul(x,y));
	printf("%d / %d = %.2f\n",x,y,div(x,y));
	return 0;
}

int *get_data(int * const dest)
{
//	int *old = dest;
	if (dest == NULL)
		return NULL;
	while(1 != scanf("%d",dest))
		getchar();
	while(1 != scanf("%d",dest + 1))
		getchar();
	return dest;
}


int add(int x,int y)
{
	return x + y;
}
int sub(int x,int y)
{
	return x - y;
}
int mul(int x,int y)
{
	return x * y;
}
float div(int x,int y)
{
	if(y == 0)
		return 0.0;
	return x / (float)y;
}
