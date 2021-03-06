#ifndef _INT_H
#define _INT_H

#include <stdio.h>
#include <stdlib.h>


void * int_copy(const void *);

int int_print(FILE *, const void *);

int int_print_tree(FILE *fd, const void *i);

int int_cmp(const void * , const void *);

void int_destroy(void * i);


#endif