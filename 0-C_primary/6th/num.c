#include <stdio.h>
#define  N 10
#define DEBUG  1

void sort_data(int * const head,const int nu);
void show_data(int *const head,const int nu);

int main()
{
	int a[N] = {0};
	int b[N] = {0};
	int c[2 * N] = {0};

	int *pa = a,
		*pb = b,
		*pc = c;
	int an = 0,
		bn = 0,
		i = 1,
		n  = 0;
/*****   get data ************/
	puts("intput your number:");
	do
	{
		while(!scanf("%d",pa))
			getchar();
		if(*pa == 0)
			break;
		else
			pa ++;
	}while(pa - a < N);
	an = pa - a;
	do
	{
		while(!scanf("%d",pb))
			getchar();
		if(*pb == 0)
			break;
		else
			pb ++;
	}while(pb - b < N );
	bn = pb - b;
/*******  sort data  ***************/
	sort_data(a,an);
	sort_data(b,bn);
	pa = a;
	pb = b;
	for(i = 0; i < an + bn; i ++)
	{
		if(*pa > *pb && pb - b < bn)
			*pc ++ = *pb ++;
		else if(*pa <= *pb && pa -a < an)
			*pc ++ = *pa ++;
	}
	while(pa - a < an)
		*pc++ = *pa++;
	while(pb - b < bn)
		*pc++ = *pb++;

	show_data(c,an + bn);
	return 0;
}

void sort_data(int * const head,const int nu)
{
	int i,j;
	for(i = 0; i < nu; i ++)
	{
		for(j = 0; j < nu - i - 1; j ++)
		{
			if(head[j] > head[j + 1])
			{
				head[j] ^= head[j + 1];
				head[j + 1] ^= head[j];
				head[j] ^= head[j + 1];
			}
		}
	}
}

void show_data(int *const head,const int nu)
{
	int i;
	for(i = 0; i < nu; i ++)
		printf("%d\t",head[i]);
	putchar(10);
}
