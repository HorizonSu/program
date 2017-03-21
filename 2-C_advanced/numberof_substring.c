#include <stdio.h>

#define N 32
#define DIGIT 	'd'
#define UPER	'U'
#define LOWER	'L'

#define DEBUG 0

int state = 0;
int max = 0;
int count = 0;
int fun(int flag);
int get_data(char *dest, int num);

int main()
{
	char buff[N];
	char *p = buff;
	
	get_data(buff, N);
	puts(buff);
	
	while ('\0' != *p) {
		if (*p >= 'a' && *p <= 'z')
			fun(LOWER);
		else if (*p >= 'A' && *p <= 'Z')
			fun(UPER);
		else if (*p >= '0' && *p <= '9')
			fun(DIGIT);
		p ++;
	}
	
	max = max > count ? max : count;
	printf("max = %d\n",max);
	
	return 0;
}

int get_data(char *dest, int num)
{
	char ch;
	int count = 0;

	while (count < num - 1 && '\n' != (ch = getchar())) {
		if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9')
			dest[count ++] = ch;
	}
	dest[count] = '\0';

	return count;
}

int fun(int flag)
{
	if (state == flag)
		count ++;
	else {
		max = max > count ? max : count;
		count = 1;
	}
	state = flag;
#if DEBUG
	printf("max = %d\tcount = %d\n",max,count);
#endif
	return 0;
}
