CC:= gcc
CFLAGS:= -Wall -O2 


.PHONY: all clean

all: sender receiver

sender: sender.c head.h
	$(CC) $< -o $@ $(CFLAGS)
receiver: receiver.c head.h
	$(CC) $< -o $@ $(CFLAGS)

clean:
	-rm *.o sender  receiver
