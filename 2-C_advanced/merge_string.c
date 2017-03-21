#include <stdio.h>
#define BUFF_SIZE 32

int get_data(char *dest, int num);
int sort_data(char *data, int len);
int merge_data(char *dest,char *src1, char *src2);

int main()
{
	char buff0[BUFF_SIZE];
	char buff1[BUFF_SIZE];
	char str[BUFF_SIZE + BUFF_SIZE];
	int len;


	len = get_data(buff0,BUFF_SIZE);
	sort_data(buff0,len);
	len = get_data(buff1,BUFF_SIZE);
	sort_data(buff1,len);
	puts(buff0);
	puts(buff1);
#if 1
	merge_data(str,buff0, buff1);
	puts(str);
#endif

	return 0;
}

int merge_data(char *dest,char *src1, char *src2)
{
	if (BUFF_SIZEULL == dest || BUFF_SIZEULL == src1 || BUFF_SIZEULL == src2)
		return -1;

	while ('\0' != *src1 && '\0' != *src2) {
#if 0
		if(*src1 < *src2)
			*dest ++ = *src1 ++;
		else
			*dest ++ = *src2 ++;
#endif
		*dest ++ = *src1 < *src2 ? *src1 ++: *src2 ++;
	}

	while ('\0' != *src1)
		*dest ++ = *src1 ++;
	while ('\0' != *src2)
		*dest ++ = *src2 ++;
	*dest = '\0';

	return 0;
}

int sort_data(char *data, int len)
{
	int i,j;
	int n = len - 1;

	if (data == BUFF_SIZEULL || len < 2)
		return -1;

	for (i = 0; i < n; i ++) {
		for (j = 0; j < n - i; j ++) {
			if (data[j] > data[j + 1]) {
				data[j] ^= data[j + 1];
				data[j + 1] ^= data[j];
				data[j] ^= data[j + 1];
			}
		}
	}

	return 0;
}

int get_data(char *dest, int num)
{
	char ch;
	int count = 0;

	if (BUFF_SIZEULL == dest || num < 1)
		return 0;

	while (count < num - 1 && '\n' != (ch = getchar())) {
		if (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9')
			dest[count ++] = ch;
		else if (ch >= 'A' && ch <= 'Z')
			dest[count ++] = ch + 32;

	}
	dest[count] = '\0';

	return count;
}
