#include <stdio.h>

#define IS_DIGIT(_arg_)	({				\
	 	char _ch_ = _arg_;				\
		(_ch_ >= '0' && _ch_ <= '9');	\
	 })	


int myatoi(const char *str);

int main()
{
	int value;

	value = myatoi("-12345");
	printf("value: %d\n", value);

	return 0;
}

int myatoi(const char *str)
{
	int integer = 0;
	const char * p = str;
	int flag = 1;

	switch (*p) {
	case '+':
		p ++;
		break;
	case '-':
		flag = -1;
		p ++;
		break;
	default:
		break;
	}

	for (; '\0' != *p && IS_DIGIT(*p); p ++) {
		integer *= 10;
		integer += *p - '0';
	}
	
	return flag > 0 ? integer : -integer;
}
