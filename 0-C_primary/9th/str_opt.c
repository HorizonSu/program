#include <stdio.h>

char * mystrcpy(char * dest, char *src);
char * mystrcat(char *dest, char *src);
unsigned int mystrlen(char *src);

int main()
{
	char str[20] = {0};
	char *p = NULL;
	p = "hello";
	char *p1 = "world";
	int ret;
	mystrcpy(str,p);
	mystrcat(str,p1);
	ret = mystrlen(str);
	puts(str);
	printf("len = %d\n",ret);
	return 0;
}

unsigned int mystrlen(char *src)
{
	if(src == NULL)
		return 0;
#if 1
	char *head = src;
	while(*src != '\0')
		src ++;
	return src -head;
#else 
	int len = 0;
	while(*(src + len ++) != '\0');
	return len - 1;

#endif
}

char * mystrcpy(char * dest, char *src)
{
	char *old = dest;
	if(dest == NULL || src == NULL)
		return NULL;
	while(*src != '\0')
		*dest ++ = *src ++;
	*dest = '\0';
	return old;
}

char * mystrcat(char *dest, char *src)
{
	char *old;
	if(dest == NULL || src == NULL)
		return NULL;
	while(*dest != '\0')	
		dest ++;
	while(*src != '\0')
		*dest ++ = *src ++;
	*dest = '\0';
	return old;
}
