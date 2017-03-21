#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE	1024
#define ARG_SIZE	64

#define DEBUG	0

extern char *environ;

char ** argv_alloc(void);
void argv_free(char **argv);
int show_ps1(void);


int main()
{
	pid_t pid;
	char **argv = NULL;

	while (1) {
		show_ps1();
		argv = argv_alloc();
#if DEBUG
		int index;
		for(index = 0; NULL != argv[index]; index ++)
			printf("argv[%d]:%s\n", index, argv[index]);
#endif
		if (argv[0] == NULL)
			continue;
		if (!strcmp(argv[0], "exit"))
			break;
		if (-1 == (pid = fork()))
			perror("fork");
		if (0 == pid){
		/*  child */	
			if (-1 == execvp(argv[0], argv))
				perror("execvp");
			exit(EXIT_FAILURE);
		} else {
			wait(NULL);
		}
	}

	argv_free(argv);
	return 0;
}

char ** argv_alloc(void)
{
	char **argv = NULL;
	char *cmdline = NULL;
	int index;
	char *strp= NULL,
		 *argp = NULL;
	
	argv = (char **)malloc(BUFF_SIZE);
	cmdline = (char *)malloc(BUFF_SIZE);
	strp = cmdline;

	fgets(cmdline, BUFF_SIZE, stdin);
	cmdline[strlen(cmdline) - 1] = 0;
#if DEBUG
	printf("debug:\n%s\n", cmdline);
#endif

	for(index = 0; '\0' != *strp; index ++) {
		argv[index] = (char *)malloc(ARG_SIZE);
		argp = argv[index];
		
		while (32 == *strp)
			strp ++;
		while ('\0' != *strp && 32 != *strp)
			*argp ++ = *strp ++;
		*argp = '\0';
	}
	argv[index] = NULL;
#if DEBUG
	puts("---- argv_alloc  ---");
	for (index = 0; NULL != argv[index]; index ++)
		puts(argv[index]);
	puts("----------------");
#endif
	
	return argv;
}

int show_ps1(void)
{
	char hostname[BUFF_SIZE];
	char cwd[BUFF_SIZE];

	gethostname(hostname, BUFF_SIZE);
	getcwd(cwd, BUFF_SIZE);
	printf("%s@%s:%s$", getlogin(), hostname, cwd);
	fflush(stdout);
	
	return 0;
}

void argv_free(char **argv)
{
	int index;
	for (index = 0; NULL != argv[index]; index ++)
		free(argv[index]);
	free(argv);
}
