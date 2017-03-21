CC:= gcc
CFLAGS:= -Wall -O2 -c
LDFLAGS:=
OBJS:= bitree.o queue.o stack.o
OUT:= bitree

.PHONY: clean memcheck

$(OUT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
%*.o: %*.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm $(OBJS) $(OUT)
memcheck:
	-valgrind --tool=memcheck ./$(OUT)
