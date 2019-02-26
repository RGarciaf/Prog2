#include "stack_elestack.h"

#define MAXSTACK 1024
struct _Stack
{
    int top;
    EleStack *item[MAXSTACK];
};
