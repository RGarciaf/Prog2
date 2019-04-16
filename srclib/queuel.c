#include "queuel.h"

struct _Queuel
{
    List * items;
};

Queuel * queuel_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4)
{
    Queuel *q = (Queuel *)malloc(sizeof(Queuel));

    if (!q || !f1 || !f2 || !f3)
    {
        return NULL;
    }

    if(!(q->items = list_ini(f1,f2,f3,f4))){
        free(q);
        return NULL;
    }

    return q;
}

void queuel_destroy(Queuel *q)
{

    if (!q)
    {
        return;
    }

    list_destroy(q->items);

    free(q);
}

Bool queuel_isEmpty(const Queuel *q)
{
    if (!q)
    {
        return FALSE;
    }

    return list_isEmpty(q->items);
}

Bool queuel_isFull(const Queuel *q)
{
    if (!q)
    {
        return FALSE;
    }

    return list_size(q->items) == MAXQUEUEL ? TRUE : FALSE;
}

Status queuel_insert(Queuel *q, const void *pElem)
{
    if (!q || !pElem)
    {
        return ERROR;
    }

    if (queuel_isFull(q) == TRUE)
    {
        return ERROR;
    }

    return list_insertFirst(q->items,pElem);
}

void *queuel_extract(Queuel *q)
{
    if (!q)
    {
        return NULL;
    }

    if (queuel_isEmpty(q))
    {
        return NULL;
    }

    return list_extractLast(q->items);
}

int queuel_size(const Queuel *q)
{
    if (!q)
    {
        return -1;
    }

    return list_size(q->items);
    /* return MAXQUEUEL - (q->front - q->rear);*/ /* Size lista circular */
}

int queuel_print(FILE *pf, const Queuel *q)
{
    int ret = 0;

    if (!pf || !q)
    {
        return -1;
    }

    if(queuel_isEmpty(q) == TRUE){
        return fprintf(pf, "Queuel vacia.\n");
    } 

    ret += fprintf(pf, "Cola con %d elementos:\n", queuel_size(q));

    ret += list_print(pf, q->items);
    
    ret += fprintf(pf, "\n");

    return ret;
}