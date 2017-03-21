#include <stdio.h>
int main()
{
	int score;
	puts("enter your score :");
	if(!scanf("%d",&score))
	{
		puts("input must be number !");	
		return -1;
	}
	if(score > 100 || score < 0)
	{
		puts("the range of score must be [0 ~ 100] !");
		return -1;
	}
	switch(score / 10)
	{
		case 10:
		case 9:
			puts("A");
			break;
		case 8:
			puts("B");
			break;
		case 7:
			puts("C");
			break;
		case 6:
			puts("D");
			break;
		default:
			puts("NO PASS !");
			break;
	}

	return 0;

}
