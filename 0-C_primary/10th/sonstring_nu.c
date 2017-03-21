#include <stdio.h>
#define N	30
#define DEBUG 1
int getmax(const int *len,int nu);
unsigned int getlen(const char *src, int *len);
int getdata(char *dest,const int len);

int main()
{
	char str[N + 1] = "123abcde";
	int len[N] = {0};
	int index = 0;
	getdata(str,N);
	puts(str);
	index = getlen(str,len);
	printf("index = %d\n",index);
#if DEBUG
	int i;
	for(i = 0; i < 10; i ++)
		printf("%4d",len[i]);
	putchar(10);
#endif
	printf("the max = %d\n",getmax(len,index));
	return 0;
}
int getdata(char *dest,const int len)
{
	char ch = 0;
	int nu = 0;
	if(dest == NULL || len <= 0)
		return 0;
	do
	{
		ch = getchar();
		if(ch == '#')
			break;
		if(ch >= '0' && ch <= '9' ||
				ch >= 'A' && ch <= 'Z' ||
				ch >= 'a' && ch <= 'z')
			*(dest + nu ++) = ch;
	}while(nu < len);
	*(dest + nu) = '\0';
	return nu;
}
unsigned int getlen(const char *src, int *len)
{
	char flag = -1;
	int index = 0;
	if(src == NULL || len == NULL)
		return 0;
	while(*src != '\0')
	{
		if(*src >= '0' && *src <= '9')
		{
			flag == 0 ? index ++ : index;
			flag = 1;
			src ++;
			len[index] ++;
		}
		else if( *src >= 'A' && *src <= 'Z' || *src >= 'a' && *src <= 'z')
		{
			flag == 1 ? index ++ : index;
			flag = 0;
			src ++;
			len[index] ++;
		}
	}
	return index;
}

int getmax(const int *arry,int nu)
{
	int max = arry[0];
	int i = 0;
	if(arry == NULL || nu <= 0)
		return -1;
	for(i = 1; i <= nu; i ++)
		max = arry[i] > max ? arry[i] : max;
	return max;
}
