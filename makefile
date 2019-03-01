CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -std=gnu99
COMPILE = -c
LIB = -Llib -lsource
HEADERS = -I includes

SRC = src/
SRCLIB = srclib/

EXE = p1_e1 p1_e2

all: clean $(EXE) clear


clean:
	rm -f $(EXE) *.o *.h.gch lib/*

clear:
	rm -f *.o *.h.gch

libsource.a: node.o graph.o stack_elestack.o elestack.o
	ar rcs lib/libsource.a $^

p1_e1: $(SRC)p1_e1.c libsource.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB) -o $@

p1_e2: $(SRC)p1_e2.c libsource.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB) -o $@

p2_e1: $(SRC)p2_e1.c libsource.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB) -o $@


node.o : $(SRCLIB)node.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) $(COMPILE) $^ $(HEADERS)

graph.o : $(SRCLIB)graph.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) $(COMPILE) $^ $(HEADERS)

stack_elestack.o : $(SRCLIB)stack_elestack.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) $(COMPILE) $^ $(HEADERS)

elestack.o : $(SRCLIB)elestack.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) $(COMPILE) $^ $(HEADERS)

execute: ejercicio1_execute 

ejercicio1_execute:
		@echo Ejecutando $@
		@echo "./p1_e1 
		@./p1_e1
		@echo "\n"