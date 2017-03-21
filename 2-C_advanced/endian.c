#include <stdio.h>

int main()
{
#if 0
	int value = 1;

	if (*(char *)&value)
		puts("little endian");
	else
		puts("big endian");
#else
	union {
		int i;
		char ch;
	}u;

	u.i = 1;
	if (u.ch)
		puts("little endian");
	else
		puts("big endian");
#endif

	return 0;
}
