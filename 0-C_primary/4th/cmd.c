#include <stdio.h>
int main()
{
	int cmd = 0;
	scanf("%d",&cmd);

	switch(cmd / 10)
	{
	case 1:
		switch(cmd % 10)
		{
		case 1:
			puts("A");
			break;
		case 2:
			puts("B");
			break;
		case 3:
			puts("C");
			break;
		default:
			puts("CMD ERROR !");
			break;
		}
		break;
	case 2:
		switch(cmd % 10)
		{
		case 1:
			puts("D");
			break;
		case 2:
			puts("E");
			break;
		case 3:
			puts("F");
			break;
		default:
			puts("CMD ERROR !");
			break;
		}
		break;
	case 3:
		switch(cmd % 10)
		{
		case 1:
			puts("G");
			break;
		case 2:
			puts("H");
			break;
		case 3:
			puts("I");
			break;
		default:
			puts("CMD ERROR !");
			break;
		}
		break;
	default:
			puts("CMD ERROR !");
		break;
	}
	return 0;

}
