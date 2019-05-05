#include "stack_fp.h"
#define MAXSTACK 100
#define EMPTY_STACK -1
extern int errno;
struct _Stack
{
    int top;
    void *item[MAXSTACK];

    P_stack_ele_destroy pf_destroy;
    P_stack_ele_copy pf_copy;
    P_stack_ele_print pf_print;
};

Stack *stack_ini(P_stack_ele_destroy fd, P_stack_ele_copy fc, P_stack_ele_print fp)
{
    Stack *s;
    int i;

    s = (Stack *)malloc(sizeof(Stack));
    if (!s)
    {
        fprintf(stderr, "%s", strerror(errno));
        return NULL;
    }
    // Inicializo tope y asigno los punteros a función
    s->top = -1;
    s->pf_copy = fc;
    s->pf_destroy = fd;
    s->pf_print = fp;

    // Asigno los punteros de los elementos
    for (i = 0; i < MAXSTACK; i++)
        s->item[i] = NULL;

    return s;
}

void stack_destroy(Stack *stc)
{
    if (!stc)
        return;

    while (stc->top != EMPTY_STACK)
    {
        stc->pf_destroy(stc->item[stc->top]); // Llamada a la función cuyo puntero se almacenó como campo
                                            // de la pila, es decir, utilizando el puntero a la función
        stc->top--;
    }
    free(stc);
}

Status stack_push(Stack * s, const void * ele){
    void * eleCopy;
    
    if (!s || !ele)
    {
        return ERROR;
    }

    if (!(eleCopy = s -> pf_copy(ele)))
    {
        return ERROR;
    }

    s->item[++s->top] = eleCopy;

    return OK;
}

void *stack_pop(Stack * s){
    void * ele;

    if (!s)
    {
        return NULL;
    }

    if(s->top < 0){
        return NULL;
    }

    if (!(ele = s->item[s->top--]))
    {
        s->top++;
        return NULL;
    }

    return ele;
}

Bool stack_isEmpty(const Stack * s){
    if (!s)
    {
        return FALSE;
    }

    /* Si ESTA VACIA devuelvo TRUE */
    return s->top == -1 ? TRUE : FALSE; /* FALSE = 0, TRUE = 1 */
}

Bool stack_isFull(const Stack * s){
    if (!s)
    {
        return FALSE;
    }

    /* Si ESTA LLENA devuelvo TRUE */
    return s->top == MAXSTACK - 1 ? 1 : 0; /* FALSE = 0, TRUE = 1 */
}

int stack_print(FILE * f, const Stack * s){
    int i, ret = 0;

    if (!s || !f)
    {
        return -1;
    }

    for (i = s->top; i > -1; i--)
    {
        ret += s -> pf_print (f, s->item[i]);
        fprintf(f, "\n");
    }

    return ret;
}

int stack_getNelements(Stack * s){
    if (!s)
    {
        return -1;
    }
    return s->top +1;
}