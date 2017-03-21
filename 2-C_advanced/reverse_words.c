#include <stdio.h>
#define BUFF_SIZE 1024

int get_data(char *dest, int num);
int reverse_word(char *str);

int main()
{
	char buff[BUFF_SIZE];

//	get_data(buff,BUFF_SIZE);
	gets(buff);
	puts(buff);
	reverse_word(buff);
	puts(buff);

	return 0;
}

void swap(char *head, char *tail)
{
	while (head < tail) {
		*head ^= *tail;
		*tail ^= *head;
		*head ++ ^= *tail --;
	}
}

int reverse_word(char *str)
{
	char *head = str,
		 *tail = str;

	while ('\0' != *tail)
		tail ++;
	swap(head, tail - 1);

	while ('\0' != *head) {
		while (32 == *head)
			head ++;
		tail = head;
		while (32 != *tail && '\0' != *tail)
			tail ++;
		swap(head, tail - 1 );
		head = tail;
	}


	return 0;
}

int get_data(char *dest, int num)
{
	char ch;
	int count = 0;

	if (NULL == dest || num < 1)
		return 0;

	while ('\n' != (ch = getchar()) && count < num - 1) {
		if (ch >= 'a' && ch <= 'z');
		else if (ch >= 'A' && ch <= 'Z')
			ch += 32;
		else
			ch = 32;
		dest[count ++] = ch;
	}
	dest[count] = '\0';

	return count;
}
