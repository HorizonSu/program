#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE_1KB	(1 << 10)
#define SIZE_1MB	(1 << 20)

int size;

void test_stacksize(void)
{
	char pad[SIZE_1MB];

	printf("%d\n", size ++);
	test_stacksize();
}

void test_fileno(void)
{
	int count;
	int fd;

	for (count = 0; ; count ++) {
		if (-1 == (fd = open("/tmp/test", O_CREAT, 0644)))
			break;
	}
	printf("max file: %d\n", count);
}


int main()
{
	struct rlimit rlim;

#if 0
	if (-1 == getrlimit(RLIMIT_STACK, &rlim))
		perror("getrlimit.RLIMIT_STACK");
	printf("soft:%ldMB\n", rlim.rlim_cur / SIZE_1MB);
	printf("hard:%ldMB\n", rlim.rlim_max);

	rlim.rlim_cur <<= 3;
	if (-1 == setrlimit(RLIMIT_STACK, &rlim))
		perror("setrlimit.RLIMIT_STACK");
	
	if (-1 == getrlimit(RLIMIT_STACK, &rlim))
		perror("getrlimit.RLIMIT_STACK");
	printf("soft:%ldMB\n", rlim.rlim_cur / SIZE_1MB);
	printf("hard:%ldMB\n", rlim.rlim_max);

	test_stacksize();
#endif

	if (-1 == getrlimit(RLIMIT_NOFILE, &rlim))
		perror("getrlimit.RLIMIT_NOFILE");
	printf("soft:%ld\n", rlim.rlim_cur);
	printf("hard:%ld\n", rlim.rlim_max);

//	test_fileno();

#if 1 
	rlim.rlim_cur = rlim.rlim_max + 1;
	if (-1 == setrlimit(RLIMIT_NOFILE, &rlim))
		perror("setrlimit.RLIMIT_NOFILE");
	
	if (-1 == getrlimit(RLIMIT_NOFILE, &rlim))
		perror("getrlimit.RLIMIT_NOFILE");
	printf("soft:%ld\n", rlim.rlim_cur);
	printf("hard:%ld\n", rlim.rlim_max);
#endif
	
	test_fileno();

	return 0;
}

