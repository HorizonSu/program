CC:= gcc
CFLAGS:= -Wall -O2 -c

.PHONY:clean

arp: arp.o netdevice.o main.o
	$(CC) -o $@ $^
main.o:main.c arp.h
	$(CC) $(CFLAGS) -o $@ $<
arp.o:arp.c arp.h
	$(CC) $(CFLAGS) -o $@ $<
netdevice.o: netdevice.c netdevice.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-rm *.o arp
