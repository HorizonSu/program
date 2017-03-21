CC:= gcc
CFLAGS:= -Wall -O2 -c
LDFLAGS:=
OBJS:= main.o queue.o stack.o
OUT:= ballclock

.PHONY: clean memcheck

$(OUT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
main.o: main.c
	$(CC) $(CFLAGS) -o $@ $^
queue.o: queue.c
	$(CC) $(CFLAGS) -o $@ $^
stack.o: stack.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm $(OBJS) $(OUT)
memcheck:
	-valgrind --tool=memcheck ./$(OUT)
