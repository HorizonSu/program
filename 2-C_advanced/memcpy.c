#include <stdio.h>

#define OPTIMIZE	1

#if OPTIMIZE

void *mymemcpy(void *dest, const void *src, int nbyte)
{
	register int *d4 = dest;
	register const int *s4 = src;
	register char *d1;
	register const char *s1;
	register int n = nbyte >> 2;
	register int i;

	for (i = 0; i < n; i++)
		*d4++ = *s4++;

	d1 = (char *)d4;
	s1 = (char *)s4;
	n = nbyte & 0x3;
	for (i = 0; i < n; i++)
		*d1++ = *s1++;

	return dest;
}


#else

void *mymemcpy(void *dest, const void *src, int nbyte)
{
	char *d = dest;
	const char *s = src;
	int i;

	for (i = 0; i < nbyte; i++)
		*d++ = *s++;

	return dest;
}
#endif

int main()
{
#if 0
	int a[10] = {1,2,3,4,5,6,7,8,9,0};
	int b[10];
	int i;

	mymemcpy(b, a, sizeof(a));
	for (i = 0; i < 10; i++)
		printf("%d\n", b[i]);
#else
	char a[1024 * 1024];
	char b[1024 * 1024];
	int i;

	for (i = 0; i < 1000; i++)
		mymemcpy(a, b, sizeof(a));
#endif

	return 0;
}
