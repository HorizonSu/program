#include <stdio.h>
#define	MONTH1	31
#define	MONTH3	31
#define	MONTH4	30
#define	MONTH5	31
#define	MONTH6	30
#define	MONTH7	31
#define	MONTH8	31
#define	MONTH9	30
#define	MONTH10	31
#define	MONTH11	30

int main()
{
	int year = 0,
		month = 0,
		day = 0,
		sum = 0,
		flag = 0;

/**************** input and check data  ********************/
	puts("input your date like : 2012-12-31 ");
	if(3 != scanf("%d-%d-%d",&year,&month,&day))
		goto Error;
	if(day > 31 || day < 1 || month > 12 || month < 0)
		goto Error;
	if( day > 30 )
	{
		if(4 == month || 6 == month || 9 == month || 11 == month)
			goto Error;
	}
	if(!(year % 4) && (year % 100) || !(year % 400))
		flag = 1;
	if(2 == month && flag)
	{
		if(day > 29)
			goto Error;
	}
	else if (2 == month && !flag)
	{
		if(day > 28)
			goto Error;
	}

/**********  kernel code   ********************/

	switch(month)
	{
		case 12:
			sum += MONTH11;
		case 11:
			sum += MONTH10;
		case 10:
			sum += MONTH9;
		case 9:
			sum += MONTH8;
		case 8:
			sum += MONTH7;
		case 7:
			sum += MONTH6;
		case 6:
			sum += MONTH5;
		case 5:
			sum += MONTH4;
		case 4:
			sum += MONTH3;
		case 3:
			sum += flag ? 29 : 28;
		case 2:
			sum += MONTH1;
		case 1:
			sum += day;
		default:
			break;
	}
	printf("the date \"%d-%02d-%02d\" is the %dth day\n",year,month,day,sum);
	return 0;
Error:
	puts("date error !");
	return -1;

}
