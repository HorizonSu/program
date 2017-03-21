CC:= gcc
CFLAGS:= -Wall -O2 


.PHONY: all clean

all: writer reader

writer: writer.c 
	$(CC) $< -o $@ $(CFLAGS)
reader: reader.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	-rm *.o writer  reader
