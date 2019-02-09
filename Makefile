CC=gcc
CFLAGS=-Wall -ansi -pedantic

all = clean p1_e1

clean:
	rm *.o p1_e1

p1_e1: p1_e1.c node.o
	$(CC) $(CFLAGS) $^ -o $@

node.o: node.c node.h
	$(CC) -c $(CFLAGS) $< -o $@
