#include <stdio.h>

#define BUFF_SIZE	32
#define IS_DIG(_ch_)	(_ch_ >= '0' && _ch_ <= '9')
#define IS_DOT(_ch_)	('.' == _ch_)

int ip2int(const char *ipstr, int *ipbuff);

int main()
{
	char buff[BUFF_SIZE];
	int ip_32;

	gets(buff);
	
	if ( 0 > ip2int(buff, &ip_32)) {
		puts("invalid ip !!");		
		return -1;
	}

	printf("%s->%#x\n", buff, ip_32);
	return 0;
}

int ip2int(const char *ipstr, int *ipbuff)
{
	const char *p = ipstr;
	int ip_8 = 0,
		ip_32 = 0;
	int n_dot = 0,
		n_dig = 0;

	for (; '\0' != *p; p ++) {
		if (IS_DIG(*p)) {
			ip_8 *= 10;
			ip_8 += *p - '0';

			n_dig ++;
		} else if (IS_DOT(*p)) {
			if(ip_8 > 255 || ip_8 < 0 || n_dig < 1)
				return -1;
			ip_32 <<= 8;
			ip_32 += ip_8;
			
			n_dot ++;
			ip_8 = 0;
			n_dig = 0;
		} else {
			return -1;
		}
	}

	if (ip_8 > 255 || ip_8 < 0 || n_dig < 1 || n_dot != 3)
		return -1;
	ip_32 <<= 8;
	ip_32 += ip_8;
	
	*ipbuff = ip_32;

	return 0;
}
