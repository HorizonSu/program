CC=gcc
CFLAG=-Wall -O2

all:exec.out execve_test.out

exec.out:exec.c
	$(CC) $(CFLAG) $< -o $@
execve_test.out:execve_test.c
	$(CC) $(CFLAG) $< -o $@

.PHONY:clean

clean:
	-rm *.out
