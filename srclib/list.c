#include "list.h"

typedef struct _NodeList
{ /* EdD privada, necesaria para implementar lista */
    void *info;
    struct _NodeList *next;
} NodeList; /* Tipo NodeList privado */
struct _List
{
    NodeList *last; /*La LEC apunta al último nodo y el último al primero*/
    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
    cmp_element_function_type cmp_element_function;
};

NodeList *nodelist_ini(List *l, void *info, NodeList *next);
void nodelist_destroy(List *l, NodeList *nl);
NodeList *nodelist_findPreviouse(NodeList *nl, NodeList *objetive);

List *list_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4)
{
    List *l = (List *)malloc(sizeof(List));

    if (!l)
    {
        return NULL;
    }

    l->destroy_element_function = f1;
    l->copy_element_function = f2;
    l->print_element_function = f3;
    l->cmp_element_function = f4;

    return l;
}

NodeList *nodelist_ini(List *l, void *info, NodeList *next)
{
    NodeList *nl = (NodeList *)malloc(sizeof(NodeList));

    if (!nl || !info || !next)
    {
        return NULL;
    }

    nl->info = l->copy_element_function(info);
    nl->next = next;

    return nl;
}

void list_destroy(List *l)
{
    if (!l)
    {
        return;
    }

    l->destroy_element_function(l->last);
}

void nodelist_destroy(List *l, NodeList *nl)
{
    if (!nl)
    {
        return;
    }

    l->destroy_element_function(nl->info);
    nodelist_destroy(nl->next);
    free(nl);
}

Status list_insertFirst(List *l, const void *pelem)
{
    NodeList *aux = NULL;

    if (!l || !pelem)
    {
        return ERROR;
    }

    if (!(aux = nodelist_ini(l, pelem, l->last->next)))
    {
        return ERROR;
    }

    l->last->next = aux;

    return OK;
}

Status list_insertLast(List *l, const void *pelem)
{
    NodeList *aux = NULL;

    if (!l || !pelem)
    {
        return ERROR;
    }

    if (!(aux = nodelist_ini(l, pelem, l->last->next)))
    {
        return ERROR;
    }

    l->last->next = aux;

    l->last = aux;

    return OK;
}

Status list_insertInOrder(List *l, const void *pelem)
{
    if (!l || !pelem)
    {
        return ERROR;
    }

    if (l->cmp_element_function(l->last->info, pelem) <= 0)
    {
        return list_insertLast(l, pelem);
    }

    return nodelist_insertInOrder(l, l->last->next, pelem);
}

Status nodelist_insertInOrder(List *l, NodeList *nl, const void *pelem)
{
    NodeList *aux;

    if (!l || !nl || !pelem)
    {
        return ERROR;
    }

    if (l->cmp_element_function(nl->next->info, pelem) >= 0)
    {
        if (!(aux = nodelist_ini(l, pelem, nl->next)))
        {
            return ERROR;
        }
        nl->next = aux;
        return Ok;
    }

    return nodelist_insertInOrder(l, nl->next, pelem);
}

void *list_extractFirst(List *l)
{
    NodeList *aux;

    if (!l)
    {
        return NULL;
    }

    aux = l->last->next;

    l->last->next = l->last->next->next;

    return aux;
}

void *list_extractLast(List *l)
{
    NodeList *aux, nl;

    if (!l)
    {
        return NULL;
    }

    aux = nodelist_findPreviouse(l->last->next, l->last);

    aux->next = l->last->next;

    nl = l->last;

    l->last = aux;

    return nl;
}

NodeList *nodelist_findPreviouse(NodeList *nl, NodeList *objetive)
{
    if (!nl || !objetive)
    {
        return NULL;
    }

    if (nl->next != objetive)
    {
        return nodelist_findPreviouse(nl->next, objetive);
    }

    return nl;
}

Bool list_isEmpty(const List *l)
{
    if (!l)
    {
        return FALSE;
    }

    return l->last ? TRUE : FALSE;
}

const void *list_get(const List *l, int index)
{
    if(!l || index < 0){
        return NULL;
    }

    return nodelist_get(l->last->next, index);

}

const void *nodelist_get(const NodeList *nl, int index)
{
    if (!nl || index < 0)
    {
        return NULL;
    }

    if (index > 0)
    {
        return nodelist_get(nl->next, index - 1);
    }
    return nl->info;
}

int list_size(const List *l)
{
}

int list_print(FILE *fd, const List *l)
{
}
