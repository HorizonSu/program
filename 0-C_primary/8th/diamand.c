#include <stdio.h>

int main()
{
	int i,j;
	int nu;
	int index_1 = 0,
		index_2 = 0;
	puts("input your number:");
	while(1 != scanf("%d",&nu))
		getchar();
	char  ch[2 *nu][2*(nu + 1)];
	printf("sizeof ch = %d\n",sizeof(ch));
	for(i = 0; i < nu; i ++,index_1 ++)
	{
		index_2 = 0;
		for(j = nu - i; j > 0; j --,index_2 ++)
			ch[index_1][index_2] = '.';
		for(j = 0; j < 2 * i + 1; j ++,index_2 ++)
			ch[index_1][index_2] = '*';
		for(j = nu - i; j > 0; j --,index_2 ++)
			ch[index_1][index_2] = '.';
		ch[index_1][index_2] = '\n';
	}
	for(i = 0; i < nu -1; i ++ ,index_1 ++)
	{
		index_2 = 0;
		for(j = 0;j < i + 2; j ++ ,index_2 ++)
			ch[index_1][index_2] = '.';
		for(j = 2 * (nu - i) - 3; j > 0; j --,index_2 ++ )
			ch[index_1][index_2] = '*';
		for(j = 0;j < i + 2; j ++ ,index_2 ++)
			ch[index_1][index_2] = '.';
		ch[index_1][index_2] = '\n';
	}
	ch[index_1][0] = '\0';
#if 0
	for(i = 0; i <= 2 * nu; i ++)
	{
		for(j = 0; j < 2 * (nu + 1); j ++)
			printf("%4d",ch[i][j]);
		putchar(10);
	}
#endif
	puts((char *)ch);

	return 0;
}

