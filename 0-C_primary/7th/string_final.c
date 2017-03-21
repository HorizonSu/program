#include <stdio.h>
#define N 20

void sort_data(char *const src,const unsigned int n);
unsigned int get_data(char *const dest,const unsigned int n );
char * mystrcat(char *dest, const char * src);
void show_data(const char *str);

int main()
{
	char str_a[2 * N] = {0};
	char str_b[N] = {0};
	unsigned int len_a,len_b;
	len_a = get_data(str_a,N);
	len_b = get_data(str_b,N);
	show_data(str_a);
	show_data(str_b);
	sort_data(str_a,len_a);
	sort_data(str_b,len_b);

	mystrcat(str_a,str_b);
	show_data(str_a);
	return 0;
}

void sort_data(char *const src,const unsigned int n)
{
	int i,j;
	if(src == NULL || n < 1)
		return;
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
unsigned int get_data(char *const dest,const unsigned int n )
{
	char ch;
	char *p = dest;
	if(dest == NULL || n < 1)
		return 0;
	while(p - dest < n && '#' != (ch = getchar()) )
	{
		if(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
			*p ++ = ch;
	}
	return p - dest;
}

char * mystrcat(char *dest, const char * src)
{
	char *old = dest;
	if(dest == NULL || src == NULL)
		return NULL;
	while(*dest != '\0')
		dest ++;
	while(*src != '\0')
		*dest ++ = *src ++;
	*dest = '\0';
	return old;
}

void show_data(const char *str)
{
	const char *p = str;
	if(str == NULL)
		return;
	while(*p != '\0')
		p ++;
	printf("string:\t%s\n",str);
	printf("length:\t%d\n",p - str);
}
