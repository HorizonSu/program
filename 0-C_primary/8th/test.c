#include <stdio.h>

int main()
{ 
#if 0
	int i = 10;
	int *p =  &i;
	int a[10];
	int *pa[10];
	int (*ap)[10];
	int **bp = &p;
	int ba[10][10];
	printf("&I = %p\n",&i);
	printf("&p = %p\n",&p);
	printf("**bp = %d\n",**bp);
#endif



#if 0
/*****************
*	pointer`s array & 2 array
* ****************/

	int i,j;
	char *a[5] = {"hello","world","love","china"};
	for(i = 0; i < 4; i ++)
	{
		for(j = 0; j < 5; j ++)
			putchar(a[i][j]  /*  *(*(a + i) + j)   */  );
		putchar(10);
	}
#endif

#if 0
/***********************
 *	array`s pointer  &&  pointer `s pointer
 * **********************/
	char a[10] = {1,2,3,4,5,6,7,8,9,10};
	char (*ap)[5] = a;
	char **bp = a;
	
	printf("** ap = %d\n",**ap);
	printf("**(ap + 1) = %d\n",**(ap + 1));
	printf("**(bp + 1) = %d\n",**(bp + 1));

#endif

#if 0
/***********************
2 array &  2 point
***************************/
	char ch;
	char *p = &ch;

	char ba[3][3] = {1,2,3,4,5,6,7,8,9};
	char **bp = ba;
	
	printf("ba = %p\n",ba);
	printf("bp = %p\n",bp);
	printf("%d\n",**(ba + 1));
	printf("%p\n",**(bp + 1));
#endif


	return 0;
}
