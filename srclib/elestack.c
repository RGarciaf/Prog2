#include "elestack.h"

struct _EleStack
{
    Node *info;
};

EleStack *EleStack_ini()
{
    EleStack *ele = (EleStack *)malloc(sizeof(EleStack));

    if (!ele)
    {
        return NULL;
    }

    ele->info = NULL;

    return ele;
}

void EleStack_destroy(EleStack *ele)
{

    if (!ele)
    {
        return;
    }

    node_destroy(ele->info);

    free(ele);
}

Status EleStack_setInfo(EleStack *ele, void *node)
{

    if (!ele || !node)
    {
        return ERROR;
    }

    return !(ele->info = node_copy((Node *)node)) ? ERROR : OK;
}

void *EleStack_getInfo(const EleStack *ele)
{
    if (!ele)
    {
        return NULL;
    }

    return (void *)node_copy(ele->info); /* Comprobar si funciona, que tengo mis dudas... si node_copy devuelve NULL...*/
}

EleStack *EleStack_copy(const EleStack *ele)
{
    EleStack *elecp;
    void *info;
    if (!ele)
    {
        return NULL;
    }

    if (!(elecp = EleStack_ini()))
    {
        return NULL;
    }

    if (EleStack_setInfo(elecp, (info = EleStack_getInfo(ele))) == ERROR)
    {
        node_destroy((Node *)info);
        EleStack_destroy(elecp);
        return NULL;
    }

    return elecp;
}

Bool EleStack_equals(const EleStack *ele1, const EleStack *ele2)
{

    if (!ele1 || !ele2)
    {
        return FALSE;
    }

    return node_cmp((Node *)ele1->info, (Node *)ele2->info) != 0 ? FALSE : TRUE;
}

int EleStack_print(FILE *f, const EleStack *ele)
{

    if (!f || !ele)
    {
        return -1;
    }

    return node_print(f, (Node *)ele->info);
}
