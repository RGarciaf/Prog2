#ifndef _STRING_H
#define _STRING_H


#include "types.h"

void * string_copy(const void *);

int string_print(FILE *, const void *);

int string_print_tree(FILE *fd, const void *i);

int string_cmp(const void * , const void *);

void string_destroy(void * i);


#endif