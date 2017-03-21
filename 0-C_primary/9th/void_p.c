#include <stdio.h>

int main()
{
	int i = 0x01020304;
	void *p = &i;
	int j;
	for(j = 0; j < 5; j ++,p ++)
	{
		if((p - (void *)&i) %  2 )
			printf("%#x\n",*((char *)p));
		else
			printf("%#x\n",*((short *)p));
		printf("p - i = %d\n",(int *)p - &i);
	}

#if 0
	if(*((char *)&i))
		puts("little");
	else
		puts("big");
#else
	*((char *)&i) ? puts("little") : puts("big");
#endif
	return 0;
}
