#include <stdio.h>

#define DAYS_MON_1	31
#define DAYS_MON_2	28
#define DAYS_MON_3	31
#define DAYS_MON_4	30
#define DAYS_MON_5	31
#define DAYS_MON_6	30
#define DAYS_MON_7	31
#define DAYS_MON_8	31
#define DAYS_MON_9	30
#define DAYS_MON_10	31
#define DAYS_MON_11	30
#define DAYS_MON_12	31

#define	USE_ARRAY	0

int main()
{
	int num = 0;
	int day;
	int mon;
	int year;
	int f_isleap = 0;
#if USE_ARRAY
	int data[12] = {DAYS_MON_1, DAYS_MON_2, DAYS_MON_3, DAYS_MON_4, DAYS_MON_5, DAYS_MON_6,
	DAYS_MON_7, DAYS_MON_8, DAYS_MON_9, DAYS_MON_10, DAYS_MON_11, DAYS_MON_12};
	int i;
#endif

	/* input */
	puts("enter your date:");
	if (3 != scanf("%d.%d.%d", &year, &mon, &day))
		goto ErrorHandler;

	/* check */
	if (year < 0 || mon < 1 || mon > 12 || day < 1 || day > 31)
		goto ErrorHandler;
	if (mon == 4 || mon == 6 || mon == 9 || mon == 11) {
		if (day > 30)
			goto ErrorHandler;
	}

	if (!(year % 4) && year % 100 || !(year % 400))
		f_isleap = 1;
	
	if (mon == 2) {
		if (day - f_isleap > 28)
			goto ErrorHandler;
	}

	/* process */
#if USE_ARRAY
	for (i = 0, num = 0; i < mon - 1; i++)
		num += data[i];
	num += day + (mon > 2 ? f_isleap : 0);
#else
	
	switch (mon) {
	case 12:
		num += DAYS_MON_11;
	case 11:
		num += DAYS_MON_10;
	case 10:
		num += DAYS_MON_9;
	case 9:
		num += DAYS_MON_8;
	case 8:
		num += DAYS_MON_7; 
	case 7:
		num += DAYS_MON_6;
	case 6:
		num += DAYS_MON_5;
	case 5:
		num += DAYS_MON_4;
	case 4:
		num += DAYS_MON_3;
	case 3:
		num += DAYS_MON_2 + f_isleap;
	case 2:
		num += DAYS_MON_1;
	case 1:
		num += day;
	}

#endif

	/* output */
	printf("THE DAY OF YEAR: %d\n", num);

	return 0;

ErrorHandler:
	puts("invalid date");
	return -1;
}
