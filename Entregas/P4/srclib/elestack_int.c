#include "elestack.h"

struct _EleStack
{
    int info;
};

EleStack *EleStack_ini()
{
    EleStack *ele = (EleStack *)malloc(sizeof(EleStack));

    if (!ele)
    {
        return NULL;
    }

    ele->info = 0;

    return ele;
}

void EleStack_destroy(EleStack *ele)
{

    if (!ele)
    {
        return;
    }

    free(ele);
}

Status EleStack_setInfo(EleStack *ele, void *info)
{

    if (!ele || !info)
    {
        return ERROR;
    }

    ele->info = *((int *) info);

    return OK;
}

void *EleStack_getInfo(const EleStack *ele)
{
    int *info = (int *)malloc(sizeof(int));
    if (!ele || !info)
    {
        return NULL;
    }

    *info = ele->info;

    return info;
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
        free(info);
        EleStack_destroy(elecp);
        return NULL;
    }

    free(info);

    return elecp;
}

Bool EleStack_equals(const EleStack *ele1, const EleStack *ele2)
{

    if (!ele1 || !ele2)
    {
        return FALSE;
    }

    return ele1->info != ele2->info ? FALSE : TRUE;
}

int EleStack_cmp(const void *ele1, const void *ele2)
{

    if (!ele1 || !ele2)
    {
        return FALSE;
    }

    return ((EleStack *) ele1)->info - ((EleStack *) ele2)->info;
}

int EleStack_print(FILE *f, const EleStack *ele)
{

    if (!f || !ele)
    {
        return -1;
    }

    return fprintf(f, "[%d] ", ele->info );
}
