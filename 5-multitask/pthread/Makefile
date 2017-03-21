CC:= gcc
CFALGS:= -Wall -O2 -c
LDFLAGS:= -lpthread

.PHONY: clean

$(OBJS).out: $(OBJS).o
	$(CC) -o $@ $^ $(LDFLAGS) 
$(OBJS).o:$(OBJS).c
	$(CC) -o $@ $^ $(CFALGS)

clean:
	-rm *.o 
	-rm *.out
