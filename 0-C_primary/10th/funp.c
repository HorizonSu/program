#include <stdio.h>
#include <string.h>

int add(int x,int y);
int sub(int x,int y);
int mul(int x,int y);
float div(int x,int y);
int getint(int x,int y);
int yushu(int x,int y);


int main()
{
	int (*ip)(int x,int y) = NULL;
	float (*fp)(int x,int y) = NULL;

	int x,y;
	if(2 != scanf("%d%d",&x,&y))
		return -1;
	ip = add;
	printf("%d + %d = %d\n",x,y,ip(x,y));
	ip = sub;
	printf("%d - %d = %d\n",x,y,ip(x,y));
	ip = mul;
	printf("%d * %d = %d\n",x,y,ip(x,y));
	fp = div;
	printf("%d / %d = %f\n",x,y,fp(x,y));
	ip = yushu;
	printf("%d %% %d = %d\n",x,y,ip(x,y));
	ip = getint;
	printf("%d / %d = %d\n",x,y,ip(x,y));

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
int yushu(int x,int y)
{
	return x % y;
}
