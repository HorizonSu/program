CC:= gcc
CFLAGS:= -Wall -O2 -c
LDFLAGS:= -lpthread -ldl
OBJS:= main.o sqlite3.o

.PHONY: clean

main:$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o:main.c sqlite3.h sqlite3ext.h
	$(CC) -o $@ $< $(CFLAGS)
sqlite3.o:sqlite3.c sqlite3.h sqlite3ext.h
	$(CC) -o $@ $< $(CFLAGS)

clean:
	-rm main $(OBJS)
