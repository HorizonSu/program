CC:=gcc
CFLAGS:=-Wall -O2
OBJS:=chat1 chat2

all: $(OBJS)

chat1: chat1.c
	$(CC) $(CFLAGS) -o $@ $^
chat2: chat2.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean

clean:
	-rm $(OBJS)
