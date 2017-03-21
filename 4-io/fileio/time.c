#include <stdio.h>
#include <time.h>

int main()
{
	time_t time_sec;
	struct tm *tms;
	char buff[128];

	time_sec = time(NULL);
	tms = localtime(&time_sec);
	puts(asctime(tms));

	strftime(buff, 128, "%Y-%m-%d %H:%M:%S\n", tms);

	puts(buff);
}
