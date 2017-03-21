#include <stdio.h>

#define IS_LETTER(_CH_)	\
	(_CH_ >= 'A' && _CH_ <= 'Z' || _CH_ >= 'a' && _CH_ <= 'z')

void swap(char *head, char *tail);

int main()
{
	char str[] = "  i    love   china     and    love you but 1 2 3 4    5  ";
	char *head = str;
	char *tail = str;

	while (*tail != '\0')
		tail ++;

	swap(head, tail - 1);

	tail = head;
	while (*head != '\0') {
		while (!IS_LETTER(*head) && *head != '\0')
			head ++;
		
		tail = head;
		while (IS_LETTER(*tail))
			tail ++;

		swap(head, tail - 1);
		head = tail;
	}

	puts(str);

	return 0;
}

void swap(char *head, char *tail)
{
	while (head < tail) {
		*head ^= *tail;
		*tail ^= *head;
		*head ^= *tail;
		head ++;
		tail --;
	}
}
