#include "int.h"

void * int_copy(const void * i){
    int * ret;
    
    if(!i){
        return NULL;
    }

    if(!(ret = (int *) malloc(sizeof(int)))){
        return NULL;
    }

    *ret = *(int*)i;

    return (void*)ret;
}

int int_print(FILE * fd, const void * i){
    if(!i){
        return -1;
    }

    return fprintf(fd, "%d\n", *(int*)i);
}

int int_cmp(const void * i1, const void *i2){
    if(!i1 || !i2){
        return -1;
    }

    return *(int*)i1 - *(int*)i2;
}

void int_destroy(void * i){
    free(i);
}