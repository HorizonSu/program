#include <stdio.h>
#include <math.h>

#define BC	'0'
#define FC	'0'

void show_color_char(int ch, int fcolor, int bcolor)
{
	fcolor %= 10;
	bcolor %= 10;

	/*background color is ignored */
	printf("\e[1;3%dm%c\e[0m", fcolor, ch);
	return;
}

int main()
{
	float x, y;
	float r = 40.0;
	int i;
	int j;
	float l;
	float scale = 2.5;

	for (i = 0; i < r * scale /5; i++) {
		for (j = 0; j < r * scale * 2; j++)
			show_color_char(BC, 3, 3);
		putchar(10);
	}
	
	for (x = -r; x <= r; x+= 1) {
		l = sqrt(r*r - x*x);

#if 0
		for (j = 0; j < r *scale; j++)
			show_color_char(BC, 7, 7);
#endif

		for (i = 0; i < r * scale; i++) {
			if (i < (r-l)*scale)
				show_color_char(BC, 7, 7);
			else
				show_color_char(FC, 1, 1);
		}

		for (i = 0; i < r * scale; i++) {
			if (i < l * scale)
				show_color_char(FC, 1, 1);
			else
				show_color_char(BC, 7, 7);
		}
#if 0
		for (j = 0; j < r *scale; j++)
			show_color_char(BC, 7, 7);
#endif

		putchar(10);
	}
	
	for (i = 0; i < r * scale /5; i++) {
		for (j = 0; j < r * scale * 2; j++)
			show_color_char(BC, 3, 3);
		putchar(10);
	}

	return 0;
}
