#include <stdio.h>

#define BUFF_SIZE	30
#define F_SPACE		1
#define F_LETTER	0

#define IS_LETTER(_ch_)	(_ch_ >= 'a' && _ch_ <= 'z' || _ch_ >= 'A' && _ch_ <= 'Z')

int main()
{
	char *str = "  i  love  china , hello,wolrd ";
	char *p = str;
	int flag = F_SPACE;
	int counter = 0;
	
	for (p = str; '\0' != *p; p++) {
		if (IS_LETTER(*p)) {
			counter += flag;
			flag = F_LETTER;
		} else {
			flag = F_SPACE;
		}
	}

	printf("%d\n", counter);

	return 0;
}
