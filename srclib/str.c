#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

void *string_copy(const void *i)
{
    char *ret;

    if (!i)
    {
        return NULL;
    }

    if (!(ret = (char *)malloc(sizeof(char) * strlen((char *) i) + 1)))
    {
        return NULL;
    }

    strcpy(ret, (char *)i);

    return (void *)ret;
}

int string_print(FILE *fd, const void *i)
{
    if (!i)
    {
        return -1;
    }

    return fprintf(fd, "%s\n", (char *)i);
}

int string_print_tree(FILE *fd, const void *i)
{
    if (!i)
    {
        return -1;
    }

    return fprintf(fd, " %s", (char *)i);
}

int string_cmp(const void *i1, const void *i2)
{
    if (!i1 || !i2)
    {
        return -1;
    }

    return strcmp((char *)i1, (char *)i2);
}

void string_destroy(void *i)
{
    free(i);
}