#include <stdio.h>
#define BUFF_SIZE 64

char *mystrstr(char *src, char *needle);

int main()
{
	char buff[BUFF_SIZE];
	char *needle = "aac";

	gets(buff);

	mystrstr(buff,needle);
	puts(buff);
	
	return 0;
}

char *mystrstr(char *src, char *needle)
{
	int len = 0;
	int i = 0;

	while ('\0' != *src) {
		len = 0;
		while (*src != *needle && *src != '\0')
			src ++;
		while (src[len] == needle[len] && needle[len] != '\0')
			len ++;
		if (needle[len] == '\0') {
			for (i = 0; i < len; i ++)
				src[i] = '*';
			src += len;
		} else {
			src ++;
		}
	}
} 
