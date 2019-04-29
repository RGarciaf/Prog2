#include "tree.h"

typedef struct _NodeBT
{
    void *info;
    struct _NodeBT *left;
    struct _NodeBT *right;
} NodeBT;

struct _Tree
{
    NodeBT *root;

    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
    cmp_element_function_type cmp_element_function;
};

Tree *tree_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4)
{
    Tree *t = (Tree *)malloc(sizeof(Tree));

    if (!t)
        return NULL;

    t->destroy_element_function = f1;
    t->copy_element_function = f2;
    t->print_element_function = f3;
    t->cmp_element_function = f4;

    return t;
}

Bool tree_isEmpty(const Tree *pa)
{
    if (!pa)
        return FALSE;
    if (!pa->root)
        return TRUE;
    return FALSE;
}

void tree_free(Tree *pa)
{
    if (!pa)
        return;
    
    if(tree_isEmpty(pa) == TRUE){
        free(pa);
        return;
    }

    

}

Status tree_insert(Tree *pa, const void *po)
{
}

Status tree_preOrder(FILE *f, const Tree *pa)
{
}

Status tree_inOrder(FILE *f, const Tree *pa)
{
}

Status tree_postOrder(FILE *f, const Tree *pa)
{
}

int tree_depth(const Tree *pa)
{
}

int tree_numNodes(const Tree *pa)
{
}

Bool tree_find(Tree *pa, const void *pe)
{
}
