#include <stdio.h>

#define BUFF_SIZE	16
int int2string(int value, char *buff);
int swap(char *buff);

int main()
{
	char buff[BUFF_SIZE];
	
	int2string(1234567890, buff);
	puts(buff);

	return 0;
}

int int2string(int num, char *buff)
{
	char *p = buff;
	int value;

	value = num < 0 ? -num : num;

	/* int to string */
	for (p = buff; value / 10; p ++) {
		*p = value % 10 + '0';
		value /= 10;
	}
	*p++ = value + '0';
	if (num < 0)
		*p++ = '-';
	*p = '\0';

	swap(buff);

	return 0;
}

int swap(char *buff)
{
	char *head = buff;
	char *tail = buff;

	while (*tail != '\0')
		tail++;
	tail--;

	while (head < tail) {
		*head ^= *tail;
		*tail ^= *head;
		*head ^= *tail;
		head++, tail--;
	}

	return 0;
}
