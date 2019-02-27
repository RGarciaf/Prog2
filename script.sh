#compila el modulo node
gcc -c -Wall -ansi -pedantic -g node.c -o node.o
#compila el modulo graph
gcc -c -Wall -ansi -pedantic -g graph.c -o graph.o
#linca los .o creados anteriormente con el main para crear el ejecutable
gcc -Wall -ansi -pedantic -g p1_e2.c node.o graph.o -o p1_e2
