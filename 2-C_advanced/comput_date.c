#include <stdio.h>

#define MONTH1	31
#define MONTH2	28
#define MONTH3	31
#define MONTH4	30
#define MONTH5	31
#define MONTH6	30
#define MONTH7	31
#define MONTH8	31
#define MONTH9	30
#define MONTH10	31
#define MONTH11	30
#define MONTH12	31



int main()
{
	int year = 0,
		month = 0,
		day = 0,
		sum = 0,
		flag = 0;

	if (3 != scanf("%d-%d-%d",&year,&month,&day)) {
		puts("invalid format !");
		return -1;
	}

#if 0

	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) {
		puts("invalid date !");
		return -1;
	}

	if (day > 30) {
		if ( 4 == month || 6 == month || 9 == month || 11 == month) {
			puts("invalid date !");
			return -1;
		}
	}

	if (!(year % 4) && year % 100 || !(year % 400))
		flag = 1;

	if (2 == month) {
		if (day - flag > 28) {
			puts("invalid date !");
			return -1;		
		}
	}
//#else
	if (year < 1 || day < 1 ) {
		puts("invalid date !");
		return -1;
	}
	if (!(year % 4) && year % 100 || !(year % 400))
		flag = 1;
	switch (month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (day > 31) {
				puts("invalid date !");
				return -1;
			}
		case 4:
		case 6:
		case 9:
		case 11:
			if (day > 30) {
				puts("invalid date !");
				return -1;
			}
			break;
		case 2:
			if (day - flag > 28) {
				puts("invalid date !");
				return -1;		
			}
			break;
		default:
			puts("invalid date !");
			return -1;		
	}

#endif

	if (year < 1 || day < 1 || day > 31 || month < 1 || month > 12) 
		goto Error;
	if (!(year % 4) && year % 100 || !(year % 400))
		flag = 1;
	switch (month) {
	case 4:
	case 6:
	case 9:
	case 11:
		if(day > 30)
			goto Error;
		break;
	case 2:
		if(day - flag > 28)
			goto Error;
		break;
	default:
		break;
	}
/************ kernel code  ************/

	switch (month) {
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
		sum += MONTH2 + flag;
	case 2:
		sum += MONTH1;
		case 1:
			sum += day;
	}

	printf("the date \"%d-%d-%d\" is the %dth day\n",year,month,day,sum);
	return 0;

Error:
	puts("invalid date !");
	return -1;

}
