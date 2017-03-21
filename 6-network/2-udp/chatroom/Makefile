CC:= gcc
CFLAGS:= -Wall -O2
OBJS:= server client

.PHONY: clean all
	
all:$(OBJS)

server:server.c server.h head.h
	$(CC) $(CFLAGS) -o $@ $<
client:client.c head.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-rm $(OBJS)
