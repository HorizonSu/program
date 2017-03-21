#include <stdio.h>

#define BUFF_SIZE	64

char *mystrncat(char *dest, const char *src, unsigned int len);

int main(void)
{
	char *str = "1234567890";
	char buff[BUFF_SIZE] = "HELLO";

	mystrncat(buff, str, 5);
	puts(buff);

	return 0;
}

char *mystrncat(char *dest, const char *src, unsigned int len)
{
	char *p = dest;
	int index;

	while ('\0' != *p)
		p ++;
	
	for (index = 0; '\0' != src[index] && index < len; index ++)
		p[index] = src[index];
	p[index] = '\0';
	
	return dest;
}
