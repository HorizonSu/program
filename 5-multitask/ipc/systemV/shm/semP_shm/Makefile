CC:= gcc
CFLAGS:= -Wall -O2 -lpthread

.PHONY: all clean
all: officer.exe soldier.exe

officer.exe:officer.c head.h
	$(CC) $< -o $@ $(CFLAGS)
soldier.exe:soldier.c head.h
	$(CC) $< -o $@ $(CFLAGS)

clean:
	-rm *.exe
