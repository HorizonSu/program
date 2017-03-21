CC=gcc
FILEPATH=TESTFILE.txt
CFLAG=-Wall -O2 -std=c99 -pedantic
OBJ?=test

$(OBJ).out: $(OBJ).c
	$(CC) $(CFLAG) -o $@ $^

.PHONY: clean

clean:
	-rm *.out
	-rm $(FILEPATH)
	
