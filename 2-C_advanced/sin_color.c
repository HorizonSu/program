#include <stdio.h>
#include <math.h>

#define N	40
#define PI	3.14

#define	LINE	1

void show_color_char(int ch, int color)
{
	printf("\e[1;3%dm%c\e[0m", color % 10, ch);
	return;
}

int main()
{
	double i;
	double j;
	double s;

	for (i = 0; i < PI * 2 ; i += 1.0 / N * 4) {
		s = sin(i) * N;
		if (s > 0) {
			for (j = 0; j <= N; j++)
				putchar(' ');
			for (j = 0; j <= s; j ++)
#if LINE
				putchar(' ');
#endif
				show_color_char('*', j);
			putchar(10);
		} else {
			s = -s;
			for (j = 0; j <= N - s; j++)
				putchar(' ');
#if ! LINE
			for (j = 0; j <= s; j ++)
#endif
				show_color_char('*', j);
			putchar(10);
		}
	}

	return 0;
}
