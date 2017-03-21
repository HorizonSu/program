all: r s
s:sender.c head.h
	cc $^ -o $@
r:receiver.c head.h
	cc $^ -o $@

.PHONY:clean

clean:
	-rm r s 

