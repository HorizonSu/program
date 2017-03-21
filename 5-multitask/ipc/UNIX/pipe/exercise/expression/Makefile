CC:=gcc
CFALGS:= -O2 -Wall -c
AR:=ar 
ARCLAGS:= cr
LIB?=libexpress.a
OBJ:= $(LIB)
LIBS_PATH?=.

$(OBJ): express.o stack.o
	$(AR) $(ARCLAGS) -o $@ $^
	-cp $(OBJ) ../$(LIBS_PATH)
express.o:express.c express.h stack.h
	$(CC) $(CFALGS) -o $@ $<
stack.o:stack.c stack.h
	$(CC) $(CFALGS) -o $@ $<

.PHONY:clean

clean:
	-rm *.a *.o

