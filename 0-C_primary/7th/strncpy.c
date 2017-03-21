#include <stdio.h>
#include <string.h>
#define N 20
int main()
{
	char str[N] = {0};
	char *dest = str;
	char *src = "helloworld";
	int n;

	while( 0 == scanf("%d",&n))
			getchar();

/*********** strncpy *************/
	while(*src != '\0' && dest - str < n)
		*dest ++ = *src ++;
	*dest = '\0';
	while(dest - str < n)
		*dest ++ = '\0';


	puts(str);
	return 0;
}
