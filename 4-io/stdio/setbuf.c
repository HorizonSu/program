#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i;
	char buff[BUFSIZ];

	setbuf(stdout, NULL);

	for(i = 1; i < 2000; i ++)
	{
		if( ! (i % 1024))
			putchar('.');
		usleep(1000);
	//	fflush(stdout);
	}
	setvbuf(stdout, buff, _IOLBF, BUFSIZ);
	sleep(1);

	printf("helloworld");

	while(1)
		;
#if 0
#if 0
	printf("hello, world");
	printf("hello, world");
	printf("hello, world");
	printf("hello, world");
//	putchar(10);
//	while(1);
	gets(buff);
	puts(buff);
#endif
	setbuf(stdout, buff);
	int i;

//	setvbuf(stdout, NULL, _IOFBF, 0);
//	setvbuf(stdout, buff, _IOFBF, 2048);
	
	for(i = 1; i < 100000; i ++)
	{
		printf("%0128d", i);
		usleep(200000);
	}
#endif
	return 0;
}
