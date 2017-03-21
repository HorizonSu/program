CC=gcc
CFLAG=-Wall -O2 -c

expression:main.o stack.o
	$(CC)  $^ -o $@
main.o:main.c
	$(CC) $(CFLAG) $< -o $@
stack.o:stack.c stack.h
	$(CC) $(CFLAG) $< -o $@

.PHONY:clean

clean:
	-rm *.o expression


