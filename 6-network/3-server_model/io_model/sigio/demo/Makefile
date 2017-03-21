CC:= gcc
CFALGS:= -Wall -O2
OBJS:= reader writer

.PHONY: all clean

all: $(OBJS)

reader: reader.c head.h
	$(CC) $(CFALGS) -o $@ $<
writer:writer.c head.h
	$(CC) $(CFALGS) -o $@ $<

clean:
	-rm *.o $(OBJS)
