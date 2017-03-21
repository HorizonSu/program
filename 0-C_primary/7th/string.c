#include <stdio.h>
#include <string.h>

#define N 20
void sort_data(char *const src,const unsigned int n);

int main()
{
	char str_a[2 * N] = {0};
	char str_b[N] = {0};
	char *pa = str_a;
	char *pb = str_b;
	char ch;

	while(pa - str_a < N && '#' != (ch = getchar()) )
	{
		if(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
			*pa ++ = ch;
	}
	while(pb - str_b < N && '#' != (ch = getchar()) )
	{
		if(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
			*pb ++ = ch;
	}
	puts("-------------------------------");
	puts("the first string is :");
	puts(str_a);
	printf("length is :\t%d\n",pa - str_a);
	puts("-------------------------------");
	puts("the second string is :");
	puts(str_b);
	printf("length is :\t%d\n",pb - str_b);
	puts("-------------------------------");
	
	sort_data(str_a,pa - str_a);
	sort_data(str_b,pb - str_b);
	
	pa = str_a;
	pb = str_b;
	while(*pa != '\0')
		pa ++;
	while(*pb != '\0')
		*pa ++ = *pb ++;
	*pb = '\0';

	puts("the final string is :");
	puts(str_a);
	printf("length is :\t%d\n",pa - str_a);
	puts("-------------------------------");
	return 0;
}

void sort_data(char *const src,const unsigned int n)
{
	int i,j;
	for(i = 0; i < n - 1; i ++)
	{
		for(j = 0; j < n - i - 1; j ++ )
		{
			if(src[j] > src[j + 1])
			{
				src[j] ^= src[j + 1];
				src[j + 1] ^= src[j];
				src[j] ^= src[j + 1];
			}
		}
	}
}
