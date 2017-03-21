CC:=gcc
CFALGS:= -Wall -O2 -c
LIB:=libexpress.a
LIBS_PATH:=./lib


export LIBS_PATH LIB

all:main

main:main.o $(LIB)
	$(CC) -o $@ $< -lpthread -lexpress -L$(LIBS_PATH)
main.o:main.c
	$(CC) $(CFALGS) -o $@ $^ -I./expression
$(LIB):
	make -C ./expression/ 

.PHONY:clean

clean:
	-rm main *.o
	-rm ./lib/*
	make -C ./expression/ clean
