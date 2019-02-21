CC=gcc
CFLAGS=-Wall -ansi -pedantic -g

all = clean p1_e1

clean:
	rm *.o p1_e1 p1_e2

p1_e1: p1_e1.c node.o
	$(CC) $(CFLAGS) $^ -o $@

p1_e2: p1_e2.c node.o graph.o
	$(CC) $(CFLAGS) $^ -o $@

node.o: node.c node.h
	$(CC) -c $(CFLAGS) $< -o $@

graph.o: graph.c graph.h
	$(CC) -c $(CFLAGS) $< -o $@