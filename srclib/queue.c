#include "queue.h"

struct _Queue
{
    void *items[MAXQUEUE];
    int front; /*la posición del elemento que se va a extraer primero de la cola*/
    int rear;  /*la posición del primer hueco donde se puede insertar en la cola*/

    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
};

Queue *queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3)
{
    int i;
    Queue *q = (Queue *)malloc(sizeof(Queue));

    if (!q || !f1 || !f2 || !f3)
    {
        return NULL;
    }

    for (i = 0; i < MAXQUEUE; i++)
    {
        q->items[i] = NULL;
    }

    q->front = 0;
    q->rear = 0;

    q->destroy_element_function = f1;
    q->copy_element_function = f2;
    q->print_element_function = f3;

    return q;
}

void queue_destroy(Queue *q)
{

    if (!q)
    {
        return;
    }

    while (queue_isEmpty(q) == FALSE)
    {
        q->destroy_element_function(queue_extract(q));
    }

    free(q);
}

Bool queue_isEmpty(const Queue *q)
{
    if (!q)
    {
        return FALSE;
    }

    return q->rear == q->front ? TRUE : FALSE;
}

Bool queue_isFull(const Queue *q)
{
    if (!q)
    {
        return FALSE;
    }

    return q->items[q->rear] ? TRUE : FALSE;
}

Status queue_insert(Queue *q, const void *pElem)
{
    if (!q || !pElem)
    {
        return ERROR;
    }

    if (queue_isFull(q) == TRUE)
    {
        return ERROR;
    }

    q->items[q->rear++] = q->copy_element_function(pElem);

    return OK;
}

void *queue_extract(Queue *q)
{
    void * aux;

    if (!q)
    {
        return NULL;
    }

    if (queue_isEmpty(q))
    {
        return NULL;
    }

    aux = q->items[q->front];
    q->items[q->front++] = NULL;

    return aux;
}

int queue_size(const Queue *q)
{
    if (!q)
    {
        return -1;
    }

    return q->rear - q->front;
    // return MAXQUEUE - (q->front - q->rear); /* Size lista circular */
}

int queue_print(FILE *pf, const Queue *q)
{
    int i, ret = 0;

    if (!pf || !q)
    {
        return -1;
    }

    if(queue_isEmpty(q) == TRUE){
        return fprintf(pf, "Queue vacia.\n");
    } 

    ret += fprintf(pf, "Cola con %d elementos:\n", queue_size(q));

    for (i = q->front; i < q->rear; i++)
    {
        ret += q->print_element_function(pf, q->items[i]);
    }
    
    ret += fprintf(pf, "\n");

    return ret;
}