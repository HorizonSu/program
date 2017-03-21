CC:= gcc
LIBS:=-lpcap
OBJS:= framecapture.out lookupnet.out

all: $(OBJS)

framecapture.out:framecapture.c
	$(CC) -o $@ $^ $(LIBS)
lookupnet.out:lookupnet.c
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	-rm *.out
