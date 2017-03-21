#include <stdio.h>
#include <math.h>

int main()
{
	float a,b,c,s,area;			
	puts("enter three lines of triangle:");
	scanf("%f%f%f",&a,&b,&c);
	//	if(a + b > c && a + c > b && b + c > a)
	if(a >= b + c || b >= a + c || c >= a + b )
	{ 
		puts("it`s not a triangle !");
		return -1;
	}
	s = 1 / (float)2 * (a + b + c);
	area = sqrt(s * (s - a) * (s - b) * (s - c));
	printf("the area of triangle is : %.2f\n",area);
	return 0;
}
