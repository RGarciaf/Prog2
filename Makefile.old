CC=gcc
CFLAGS=-Wall -ansi -pedantic -g

all = clean p1_e1

clean:
	rm *.o p1_e1 p1_e2

p1_e1: p1_e1.c node.o
	$(CC) $(CFLAGS) $^ -o $@

p1_e2: p1_e2.c node.o graph.o
	$(CC) $(CFLAGS) $^ -o $@

p2_e1: p2_e1.c node.o elestack.o stack_elestack.o
	$(CC) $(CFLAGS) $^ -o $@

###### Practica 1 ######
node.o: node.c node.h
	$(CC) -c $(CFLAGS) $< -o $@

graph.o: graph.c graph.h
	$(CC) -c $(CFLAGS) $< -o $@

###### Practica 2 ######
stack_elestack.o: stack_elestack.c stack_elestack.h
	$(CC) -c $(CFLAGS) $< -o $@

elestack.o: elestack.c elestack.h
	$(CC) -c $(CFLAGS) $< -o $@