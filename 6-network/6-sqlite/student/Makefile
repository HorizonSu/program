CC:= gcc
CFLAGS:= -O2 -Wall -c
LDFLAGS:= -lpthread -ldl
OBJS:= sqlite3.o main.o

main:$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
main.o:main.c
	$(CC) -o $@ $^ $(CFLAGS)
sqlite3.o:sqlite3.c
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	-rm $(OBJS) main
