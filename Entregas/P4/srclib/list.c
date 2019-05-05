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

NodeList *nodelist_ini(List *l, const void *info, NodeList *next);
void nodelist_destroy(List *l, NodeList *nl);
Status nodelist_insertInOrder(List *l, NodeList *nl, const void *pelem);
NodeList *nodelist_findPreviouse(NodeList *nl, NodeList *objetive);
const void *nodelist_get(const NodeList *nl, int index);
int nodelist_get_size(NodeList *nl, NodeList *last);

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

    l->last = NULL;

    return l;
}

NodeList *nodelist_ini(List *l, const void *info, NodeList *next)
{
    NodeList *nl = (NodeList *)malloc(sizeof(NodeList));

    if (!nl || !info)
    {
        return NULL;
    }

    if (!next)
    {
        nl->next = nl;
    }
    else
    {
        nl->next = next;
    }

    nl->info = l->copy_element_function(info);

    return nl;
}

void list_destroy(List *l)
{
    NodeList * next = NULL;
    if (!l)
    {
        return;
    }

    if (!l->last) {
        free(l);
        return;
    }    

    next = l->last->next;
    l->last->next = NULL;
    nodelist_destroy(l, next);
    free(l);
}

void nodelist_destroy(List *l, NodeList *nl)
{
    NodeList * next = NULL;
    if (!nl)
    {
        return;
    }

    next = nl->next;

    l->destroy_element_function(nl->info);
    free(nl);
    nodelist_destroy(l, next);
}

Status list_insertFirst(List *l, const void *pelem)
{
    NodeList *aux = NULL;

    if (!l || !pelem)
    {
        return ERROR;
    }

    if (list_isEmpty(l) == TRUE)
    {
        aux = nodelist_ini(l, pelem, l->last);
        if (!aux)
        {
            return ERROR;
        }

        l->last = aux;
        aux->next = aux;
    }
    else
    {
        aux = nodelist_ini(l, pelem, l->last->next);
        if (!aux)
        {
            return ERROR;
        }
        l->last->next = aux;
    }

    return OK;
}

Status list_insertLast(List *l, const void *pelem)
{
    NodeList *aux = NULL;

    if (!l || !pelem)
    {
        return ERROR;
    }    

    if (list_isEmpty(l) == TRUE)
    {
        if (!(aux = nodelist_ini(l, pelem, l->last)))
        {
            return ERROR;
        }
        l->last = aux;
        aux->next = aux;
    }
    else
    {
        if (!(aux = nodelist_ini(l, pelem, l->last->next)))
        {
            return ERROR;
        }
        l->last->next = aux;

        l->last = aux;
    }

    return OK;
}

Status list_insertInOrder(List *l, const void *pelem)
{
    if (!l || !pelem)
    {
        return ERROR;
    }

    if (list_isEmpty(l) == TRUE)
    {
        return list_insertLast(l, pelem);
    }

    if (l->cmp_element_function(l->last->info, pelem) <= 0) /* Si el segundo argumento es mayor, devuelve negativo o 0 si es igual */
    {
        return list_insertLast(l, pelem);
    }

    return nodelist_insertInOrder(l, l->last, pelem);
}

Status nodelist_insertInOrder(List *l, NodeList *nl, const void *pelem)
{
    NodeList *aux;

    if (!l || !nl || !pelem)
    {
        return ERROR;
    }

    if (l->cmp_element_function(nl->next->info, pelem) >= 0) /* Si el primero es mayor que el segundo, lo insertamos antes */
    {
        if (!(aux = nodelist_ini(l, pelem, nl->next))) /* Creo un nodo que su next apunta al next de nl */
        {
            return ERROR;
        }

        nl->next = aux;
        return OK;
    }

    return nodelist_insertInOrder(l, nl->next, pelem);
}

void *list_extractFirst(List *l)
{
    NodeList *aux;
    void * ret;

    if (!l)
    {
        return NULL;
    }

    if (list_isEmpty(l) == TRUE)
    {
        return NULL;
    }

    if (list_size(l) == 1)
    {
        aux = l->last;
        l->last = NULL;
        return aux;
    }

    aux = l->last->next;

    l->last->next = l->last->next->next;

    ret = l->copy_element_function(aux->info);
    aux->next = NULL;

    nodelist_destroy(l, aux);

    return ret;
}

void *list_extractLast(List *l)
{
    NodeList *aux, *nl;
    void * ret;

    if (!l)
    {
        return NULL;
    }

    if (list_isEmpty(l) == TRUE)
    {
        return NULL;
    }

    if (list_size(l) == 1)
    {
        aux = l->last;
        l->last = NULL;

        ret = l->copy_element_function(aux->info);
        aux->next = NULL;

        nodelist_destroy(l, aux);

        return ret;
    }

    aux = nodelist_findPreviouse(l->last->next, l->last);

    aux->next = l->last->next;

    nl = l->last;

    l->last = aux;

    ret = l->copy_element_function(nl->info);
    nl->next = NULL;

    nodelist_destroy(l, nl);

    return ret;
}

NodeList *nodelist_findPreviouse(NodeList *nl, NodeList *objetive)
{
    if (!nl || !objetive)
    {
        return NULL;
    }

    if (nl == objetive)
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

    return l->last == NULL ? TRUE : FALSE;
}

const void *list_get(const List *l, int index)
{
    if (!l || index < 0)
    {
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
    if (!l)
    {
        return -1;
    }

    if (list_isEmpty(l) == TRUE)
    {
        return 0;
    }

    return nodelist_get_size(l->last->next, l->last);
}

int nodelist_get_size(NodeList *nl, NodeList *last)
{
    if (!nl)
    {
        return -999;
    }

    if (nl != last)
    {
        return 1 + nodelist_get_size(nl->next, last);
    }

    return 1;
}

int list_print(FILE *fd, const List *l)
{
    NodeList *nl = NULL;
    int ret = 0;

    if (!fd || !l)
    {
        return -1;
    }

    if (list_isEmpty(l) == TRUE)
    {
        return 0;
    }

    if (list_size(l) == 1)
    {
        return l->print_element_function(fd, l->last->info);
    }

    nl = l->last;
    do
    {
        nl = nl->next;
        ret += l->print_element_function(fd, nl->info);
    } while (l->last != nl);

    ret += fprintf(fd, "\n");

    return ret;

    /*for(nl = l->last->next; l->last != nl; nl = nl->next){
        l->print_element_function(fd, nl->info);
    }
    l->print_element_function(fd, nl->info);*/
    /* Cuando llega al ultimo elemento sale del bucle por lo que no lo llega a imprimir */
}
