CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -std=gnu99
COMPILE = -c
LIB_NODE = -Llib -lsource_node
LIB_INT = -Llib -lsource_int
HEADERS = -I includes

SRC = src/
SRCLIB = srclib/

EXE = p1_e1 p1_e2 p2_e1 p2_e2

all: clean $(EXE) clear


clean:
	rm -f $(EXE) *.o *.h.gch lib/*

clear:
	rm -f *.o *.h.gch 

libsource_node.a: node.o graph.o stack_elestack.o  elestack_node.o  
	ar rcs lib/$@ $^

libsource_int.a: node.o graph.o stack_elestack.o  elestack_int.o 
	ar rcs lib/$@ $^

p1_e1: $(SRC)p1_e1.c libsource_node.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB_NODE) -o $@

p1_e2: $(SRC)p1_e2.c libsource_node.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB_NODE) -o $@

p2_e1: $(SRC)p2_e1.c libsource_node.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB_NODE) -o $@

p2_e2: $(SRC)p2_e2.c libsource_int.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB_INT) -o $@


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

elestack_node.o : $(SRCLIB)elestack_node.c 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) $(COMPILE) $^ $(HEADERS)

elestack_int.o : $(SRCLIB)elestack_int.c
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