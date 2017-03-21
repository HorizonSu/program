#include <stdio.h>
#define N	20
#define DATATYPE	int
int main()
{
	DATATYPE a[N] = {0};
	DATATYPE *pf = a;
	DATATYPE *pt = a;
	while(pt - a < N)
	{
		while(!scanf("%d",pt))
			getchar();
		pt ++;
	}
	pt --;
	while(pf < pt)
	{
		*pf ^= *pt;
		*pt ^= *pf;
		*pf ++ ^= *pt --;
	}
	pf = a + sizeof(a)/sizeof(DATATYPE);
	while(pf - a > 0)
		printf("%d\t",* --pf);
	putchar(10);
	return 0;
}
