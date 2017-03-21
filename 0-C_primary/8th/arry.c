#include <stdio.h>
int main()
{	
	char ch[3][3] = {1,2,3,4,5,6,7,8,9};
	int i,j;

	for(i = 0; i < 3; i ++)
	{
		for(j = 0; j < 3; j ++)
			printf("%d\t",ch[i][j]);
		putchar(10);
	}
#if 1
	for(i = 0; i < 3; i ++)
	{
		for(j = 0; j < 3; j ++)
			printf("%p\t",&ch[i][j]);
		putchar(10);
	}
	 
	
	printf("&ch = %p\n",&ch + 1);
	printf("");
	printf("&ch[1][0] = %f\n",&ch[1][0]);
	printf("ch  + 1 = %f\n",ch + 1);
	printf("&ch[0][1] = %p\n",&ch[0][1]);
	printf("ch[0] = %p\n",ch[0]);
	printf("ch[0] + 1= %p\n",ch[0] + 1);
	printf("ch[1] = %p\n",ch[1]);
	printf("ch[1] + 3 = %p\n",ch[1] + 3);
	printf("*(ch[0] + 2) = %d\n",*(ch[0] + 2));

	printf("&ch[1][0] = %p\n",&ch[1][0]);
	printf("*ch[1] = %d\n",*ch[1]);
	printf("&ch[1] + 1 = %f\n",&ch[1] + 1);
	printf("*(*(ch + 1) + 1) = %d\n",*(*(ch + 1) + 1));

	printf("*(*(&ch[0] + 1) + 1) + 1 = %d\n",*(*(&ch[0] + 1) + 1) + 1);
	printf("ret = %d\n",*(*(ch + 1) + 2) + *(*(&ch[1] + 1)) + 1 );	
#endif
	
	return 0;
}
