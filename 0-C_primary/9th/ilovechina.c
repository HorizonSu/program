#include <stdio.h>
#include <string.h>
#define N	30

unsigned int  swap(char *head,char *tail);
unsigned int getdata(char * dest);

int main()
{
	int count = 0;
	char str[N + 1] = {0};
	char *head = str,
		 *tail = str;
	swap(str,str + getdata(str) - 1);
	while(*tail != '\0' && *head != '\0')
	{
		while(*head == ' ' && *head != '\0')
			head ++;
		tail = head;
		while(*tail != ' ' && *tail != '\0')
			tail ++;
		count = swap(head,tail - 1);
		head = tail;
	}
	printf("count = %d\n",count);
	puts(str);
	return 0;
}

unsigned int getdata(char * dest)
{
	char ch;
	int count = 0;
	char *old = dest;
	if(dest == NULL)
		return 0;
	while('\n' != (ch = getchar()) &&  count < N )
		*dest ++ = ch,count ++;
	*dest = '\0';
	return dest - old;
}

unsigned int swap(char * head,char *tail)
{
	static int i = 0;
	if(head == NULL || tail == NULL)
		return 0;
	while(head < tail)
	{
		*head ^= *tail;
		*tail ^= *head;
		*head ++ ^= * tail -- ;
	}
	return ++ i;
}
