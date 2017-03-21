#include <stdio.h>
int main()
{	
	char ch[3][3] = {1,2,3,4,5,6,7,8,9};
	int i,j;

	for (i = 0; i < 3; i ++) {
		for (j = 0; j < 3; j ++)
			printf("%12d",ch[i][j]);
		putchar(10);
	}

	for (i = 0; i < 3; i ++) {
		for (j = 0; j < 3; j ++)
			printf("%12p",&ch[i][j]);
		putchar(10);
	}
	 
#if 1
	
	printf("&ch + 1 = %#x\n",&ch + 1);  // char(*)[3][3];
	printf("&ch[1][0] = %#x\n",&ch[1][0]);
	printf("ch  + 1 = %#x\n",ch + 1);
	printf("ch[0] = %#x\n",ch[0]);
	printf("ch[0] + 1= %#x\n",ch[0] + 1);
	printf("ch[1] + 3 = %#x\n",ch[1] + 3);
	printf("*(ch[0] + 2) = %#x\n",*(ch[0] + 2));

	printf("*ch[1] = %#x\n",*ch[1]);
	printf("&ch[1] + 1 = %#x\n",&ch[1] + 1);// ch + 1 + 1
	printf("*(*(ch + 1) + 1) = %#x\n",*(*(ch + 1) + 1));

	printf("*(*(&ch[0] + 1) + 1) + 1 = %#x\n",*(*(&ch[0] + 1) + 1) + 1);
	printf("ret = %#x\n",*(*(ch + 1) + 2) + *(*(&ch[1] + 1)) + 1 );	
#endif
	
	return 0;
}
