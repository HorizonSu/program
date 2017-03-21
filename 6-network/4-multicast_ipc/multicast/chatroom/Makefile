CC:= gcc
CFLAGS:= -Wall -O2 


.PHONY: all clean

all: chatroom

chatroom: chatroom.c protocol.h
	$(CC) $< -o $@ $(CFLAGS)
clean:
	-rm chatroom
