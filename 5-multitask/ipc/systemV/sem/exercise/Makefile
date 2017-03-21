CC:=gcc
CFLAGS:=-Wall -O2 
OBJS:=reader writer

all:$(OBJS)

reader:reader.c head.h
	$(CC) $(CFLAGS) -o $@ $<
writer:writer.c head.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:	 clean

clean:
	-rm $(OBJS)
