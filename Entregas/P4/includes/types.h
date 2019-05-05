/*
 * File: types.h
 * Author: Profesores de PROG2
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>

typedef enum
{
    ERROR = 0,
    OK = 1,
    NO_FILE_POS_VALUES = 2 
} Status;

typedef enum
{
    FALSE = 0,
    TRUE = 1
} Bool;

typedef void (*destroy_element_function_type)(void *);
typedef void *(*copy_element_function_type)(const void *);
typedef int (*print_element_function_type)(FILE *, const void *);
typedef int (*cmp_element_function_type)(const void *, const void *);

#endif /* TYPES_H */