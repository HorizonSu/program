#include <stdio.h>

#define OPTIMIZE 1

char *mystrcpy(char *dest, const char *src);

int main()
{
	char *str = "12345678901234567890123456789012345678901234567890";
	char buff[128];
	int i;

	for (i = 0; i < 10000000; i++)
		strcpy(buff, str);
	puts(buff);


	return 0;
}

#if OPTIMIZE
char *mystrcpy(char *dest, const char *src)
{
	register int *d4 = (int *)dest;
	register const int *s4 = (const int *)src;
	register char *d1 = NULL;
	register const char *s1 = NULL;
	register int value = *s4;

	while ((value & 0xff000000) && (value & 0xff0000) 
			&& (value & 0xff00) && (value & 0xff)) {
		*d4++ = *s4++;
		value = *s4;
	}

	d1 = (char *)d4;
	s1 = (const char *)s4;
	while ('\0' != *s1)
		*d1++ = *s1++;
	*d1 = '\0';
	
	return dest;
}

#else
char *mystrcpy(char *dest, const char *src)
{
	char *old = dest;
	
	if (dest == NULL || src == NULL)
		return NULL;

	while ('\0' != *src)
		*dest++ = *src++;
	*dest = '\0';
	
	return old;
}
#endif
