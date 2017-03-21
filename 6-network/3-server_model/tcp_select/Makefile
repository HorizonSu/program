CC:= gcc
CFLAGS:= -Wall -O2

all: server client

server:server.c head.h
	$(CC) -o $@ $< $(CFLAGS)
client:client.c head.h
	$(CC) -o $@ $< $(CFLAGS)

clean:
	-rm server client
