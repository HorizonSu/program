CC:= gcc
CFLAGS:= -Wall -O2 -c
LDFLAGS:=

.PHONY: all clean

all: server client

server: server.o
	$(CC) $(LDFLAGS) -o $@ $^
client: client.o
	$(CC) $(LDFLAGS) -o $@ $^
%*.o: %*.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm *.o server client
