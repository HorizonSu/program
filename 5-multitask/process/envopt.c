#include <stdio.h>
#include <stdlib.h>

#define OVERWRITE_ENABLE	1
#define OVERWRITE_DISABLE	0

extern char **environ;

int main()
{
	int index;

	puts("-----------------------------------------");
	for (index = 0; NULL != environ[index]; index ++) {
		puts(environ[index]);
	}
	puts("-----------------------------------------");
	
	printf("befor putenv:\nMY_VALUE:%s\n", getenv("MY_VALUE"));
	putenv("MY_VALUE=helloworld");
	printf("after putenv:\nMY_VALUE:%s\n", getenv("MY_VALUE"));
	
	setenv("MY_VALUE", "ilovechina", OVERWRITE_ENABLE );
	printf("after setenv:\nMY_VALUE:%s\n", getenv("MY_VALUE"));
	
	puts("-----------------------------------------");
	for (index = 0; NULL != environ[index]; index ++) {
		puts(environ[index]);
	}
	puts("-----------------------------------------");

	printf("location of environment: %p\n", &environ);
	printf("location of environment: %p\n", environ);
	printf("location of environment: %p\n", *environ);

	return 0;
}
