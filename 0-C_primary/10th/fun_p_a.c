#include <stdio.h>
#include <string.h>

int add(int x,int y);
int sub(int x,int y);
int mul(int x,int y);
float div(int x,int y);
int getint(int x,int y);
int rem(int x,int y);


int main()
{
	int x,y,i;
	int (*funp[5])(int,int) = {add,sub,mul,getint,rem};
	float (*div_p)(int,int) = div;
	char oprt[5] = {'+','-','*','/','%'};
	if(2 != scanf("%d%d",&x,&y))
		return -1;
	for(i = 0; i < 5; i ++)
		printf("%d %c %d = %d\n",x,oprt[i],y,funp[i](x,y));
	printf("%d /%d = %f\n",x,y,div_p(x,y));

	return 0;

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
	return x / (float)y;
}
int getint(int x,int y)
{
	return x / y;
}
int rem(int x,int y)
{
	return x % y;
}
