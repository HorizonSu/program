#include <stdio.h>

int main()
{
	int i = 10;
	char ch = 64;
	if(&ch == &i)
		puts("hello");
	return 0;
}


