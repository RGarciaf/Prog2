#include "stack_elestack.h"

#define MAXSTACK 1024
struct _Stack
{
    int top;
    EleStack *item[MAXSTACK];
};

Stack *stack_ini()
{
    int i;
    Stack *s = (Stack *)malloc(sizeof(Stack));

    if (!s)
    {
        return NULL;
    }

    s->top = -1;

    for (i = 0; i < MAXSTACK; i++)
    {
        s->item[i] = NULL;
    }

    return s;
}

void stack_destroy(Stack *s)
{
    EleStack *ele;

    if (!s)
    {
        return;
    }

    while ((ele = stack_pop(s)) != NULL)
    {
        EleStack_destroy(ele);
    }

    free(s);
}

Status stack_push(Stack *s, const EleStack *ele)
{
    int top;

    EleStack *eleCopy;
    if (!s || !ele)
    {
        return ERROR;
    }

    if (!(eleCopy = EleStack_copy(ele)))
    {
        return ERROR;
    }
    top = s->top;
    
    s->item[top] = eleCopy;

    top ++;
    s->top = top;

    return OK;
}

EleStack *stack_pop(Stack *s)
{
    EleStack *ele;
    if (!s)
    {
        return NULL;
    }

    if (!(ele = s->item[--s->top]))
    {
        s->top++;
        return NULL;
    }

    return ele;
}

Bool stack_isEmpty(const Stack *s)
{
    if (!s)
    {
        return FALSE;
    }

    /* Si ESTA VACIA devuelvo TRUE */
    return s->top == -1 ? TRUE : FALSE; /* FALSE = 0, TRUE = 1 */
}

Bool stack_isFull(const Stack *s)
{
    if (!s)
    {
        return FALSE;
    }

    /* Si ESTA LLENA devuelvo TRUE */
    return s->top == MAXSTACK - 1 ? 1 : 0; /* FALSE = 0, TRUE = 1 */
}

int stack_print(FILE *f, const Stack *s)
{
    int i, ret = 0;

    if (!s || !f)
    {
        return -1;
    }

    for (i = s->top; i > -1; i--)
    {
        ret += EleStack_print(f, s->item[i]);
        fprintf(f,"\n");
    }

    return ret;
}