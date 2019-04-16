CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -std=gnu99
COMPILE = -c
LIB_NODE = -Llib -lsource_node
LIB_INT = -Llib -lsource_int
LIB = -Llib -lsource
HEADERS = -I includes

SRC = src/
SRCLIB = srclib/

EXE = p1_e1 p1_e2 p2_e1 p2_e2 p2_e1_pf p2_e2_pf p2_e4 p3_testqueue p3_e1 p3_e2 p3_testqueuel

all: clean $(EXE) clear


clean:
	rm -f $(EXE) *.o *.h.gch lib/*
	touch lib/.noMeBorres 

clear:
	rm -f *.o *.h.gch 

libsource_node.a: node.o graph.o stack_elestack.o  elestack_node.o  queue.o
	ar rcs lib/$@ $^

libsource_int.a: node.o graph.o stack_elestack.o  elestack_int.o queue.o
	ar rcs lib/$@ $^

libsource.a: node.o graph.o stack_fp.o elestack_int.o queue.o list.o int.o queuel.o
	ar rcs lib/$@ $^

p1_e1: $(SRC)p1_e1.c libsource_node.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB_NODE) -o $@

p1_e2: $(SRC)p1_e2.c libsource_node.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB_NODE) -o $@

p2_e1: $(SRC)p2_e1.c libsource_node.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB_NODE) -o $@

p2_e2: $(SRC)p2_e2.c libsource_int.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB_INT) -o $@

p2_e1_pf: $(SRC)p2_e1_pf.c libsource.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB) -o $@

p2_e2_pf: $(SRC)p2_e2_pf.c libsource.a 
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB) -o $@

p2_e4: $(SRC)p2_e4.c libsource.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB) -o $@

p3_testqueue: $(SRC)p3_testqueue.c libsource.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB) -o $@

p3_e1: $(SRC)p3_e1.c libsource.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB) -o $@

p3_e2: $(SRC)p3_e2.c libsource.a
	$(CC) $(CFLAGS) $< $(HEADERS) $(LIB) -o $@

p3_testqueuel: $(SRC)p3_testqueuel.c libsource.a
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

stack_fp.o : $(SRCLIB)stack_fp.c
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

queue.o : $(SRCLIB)queue.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) $(COMPILE) $^ $(HEADERS)

list.o : $(SRCLIB)list.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) $(COMPILE) $^ $(HEADERS)

int.o : $(SRCLIB)int.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) $(COMPILE) $^ $(HEADERS)

queuel.o : $(SRCLIB)queuel.c
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) $(COMPILE) $^ $(HEADERS)