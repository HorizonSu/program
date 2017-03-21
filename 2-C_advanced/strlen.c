#include <stdio.h>

#define OPTIMIZE	0

#if OPTIMIZE

int mystrlen(char *str)
{
	register int *tail = (int *)str;
	register int value;
	register int len = 0;
	char *p;

#if 1
	while (1) {
		value = *tail;
		if (!(value & 0xff000000) || !(value & 0xff0000)
				|| !(value & 0xff00) || !(value & 0xff))
			break;
		len += 4;
		tail++;
	}
#else
	value = *tail;
	while (value & 0xff000000 && value & 0xff0000 && value & 0xff00 && value & 0xff) {
		value = *tail;
		len += 4;
		tail++;
	}
#endif
	p = (char *)tail;

	while (*p++ != '\0')
		len ++;

	return len;
}

#else

int mystrlen(char *str)
{
	char *tail = str;

	while ('\0' != *tail)
		tail++;
	
	return tail - str;
}
#endif

int main()
{
	char *str = "12345678901234567890123456789012345678901234567890";
	int len;
	int i;
	
	for (i = 0; i < 10000000; i++)
		len = mystrlen(str);
	printf("len: %d\n", len);

	return 0;
}
