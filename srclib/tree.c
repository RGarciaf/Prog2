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

NodeBT *nodebt_ini(Tree *t, NodeBT *left, NodeBT *right, const void *info);
void nodebt_destroy(Tree *t, NodeBT *node);
Status nodebt_insert(Tree *t, NodeBT *node, const void *po);
Status nodebt_preOrder(FILE *f, const Tree *t, NodeBT *node);
Status nodebt_inOrder(FILE *f, const Tree *t, NodeBT *node);
Status nodebt_postOrder(FILE *f, const Tree *t, NodeBT *node);
int nodebt_depth(NodeBT *node);
int nodebt_numNodes(NodeBT *node);
Bool nodebt_find(Tree *t, NodeBT *node, const void *po);


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

NodeBT *nodebt_ini(Tree *t, NodeBT *left, NodeBT *right, const void *info)
{
    NodeBT *ret;

    if (!t || !info)
        return NULL;

    if (!(ret = (NodeBT *)malloc(sizeof(NodeBT))))
        return NULL;

    ret->info = t->copy_element_function(info);
    ret->left = left;
    ret->right = right;

    return ret;
}

Bool tree_isEmpty(const Tree *t)
{
    if (!t)
        return FALSE;
    if (!t->root)
        return TRUE;
    return FALSE;
}

void tree_free(Tree *t)
{
    if (!t)
        return;

    if (tree_isEmpty(t) == TRUE)
    {
        free(t);
        return;
    }

    nodebt_destroy(t, t->root);
}

void nodebt_destroy(Tree *t, NodeBT *node)
{
    if (!t || !node)
        return;

    t->destroy_element_function(node->info);

    nodebt_destroy(t, node->left);
    nodebt_destroy(t, node->right);
}

Status tree_insert(Tree *t, const void *po)
{
    if (!t || !po)
        return ERROR;

    if (tree_isEmpty(t) == TRUE)
    {
        t->root = nodebt_ini(t, NULL, NULL, po);
        return OK;
    }

    return nodebt_insert(t, t->root, po);
}

Status nodebt_insert(Tree *t, NodeBT *node, const void *po)
{
    if (!t || !po)
        return ERROR;

    if (t->cmp_element_function(node->info, po) > 0)
    {
        if (node->left != NULL)
            return nodebt_insert(t, node->left, po);

        node->left = nodebt_ini(t, NULL, NULL, po);
        return OK;
    }
    else if (t->cmp_element_function(node->info, po) < 0)
    {
        if (node->right != NULL)
            return nodebt_insert(t, node->right, po);

        node->right = nodebt_ini(t, NULL, NULL, po);
        return OK;
    }
    return ERROR; /* Si el elemento ya esta insertado devuelvo error */
}

Status tree_preOrder(FILE *f, const Tree *t) /*En profundiad imprimiendo cada nodo por el que se pasa antes de cerrarlo*/
{
    if (!f || !t)
        return ERROR;

    if (tree_isEmpty(t) == TRUE)
        return OK;

    return nodebt_preOrder(f, t, t->root);
}

Status nodebt_preOrder(FILE *f, const Tree *t, NodeBT *node)
{
    if (!f || !t || !node)
        return ERROR;

    t->print_element_function(f, node->info);

    nodebt_preOrder(f, t, node->left);
    nodebt_preOrder(f, t, node->right);

    return OK;
}

Status tree_inOrder(FILE *f, const Tree *t) /* Imprime hijo izdo, el mismo, hijo derecho */
{
    if (!f || !t)
        return ERROR;

    if (tree_isEmpty(t) == TRUE)
        return OK;

    return nodebt_inOrder(f, t, t->root);
}

Status nodebt_inOrder(FILE *f, const Tree *t, NodeBT *node)
{
    if (!f || !t || !node)
        return ERROR;

    nodebt_preOrder(f, t, node->left);
    t->print_element_function(f, node->info);
    nodebt_preOrder(f, t, node->right);

    return OK;
}

Status tree_postOrder(FILE *f, const Tree *t) /* Como pre pero imprimiendolo al final */
{
    if (!f || !t)
        return ERROR;

    if (tree_isEmpty(t) == TRUE)
        return OK;

    return nodebt_postOrder(f, t, t->root);
}

Status nodebt_postOrder(FILE *f, const Tree *t, NodeBT *node)
{
    if (!f || !t || !node)
        return ERROR;

    nodebt_preOrder(f, t, node->left);
    nodebt_preOrder(f, t, node->right);
    t->print_element_function(f, node->info);

    return OK;
}

int tree_depth(const Tree *t)
{
    if (!t)
        return -999;
    return nodebt_depth(t->root);
}

int nodebt_depth(NodeBT *node)
{
    int depthR, depthL;

    if (!node)
        return 0;

    depthR = nodebt_depth(node->right) + 1;
    depthL = nodebt_depth(node->left) + 1;

    return depthR > depthL ? depthR : depthL;
}

int tree_numNodes(const Tree *t)
{
    if(!t)
        return -1;

    return nodebt_numNodes(t->root);
}

int nodebt_numNodes(NodeBT *node)
{
    if (!node)
        return 0;

    return nodebt_numNodes(node->left) + nodebt_numNodes(node->right) + 1;
}

Bool tree_find(Tree *t, const void *pe)
{
    if(!t || !pe)
        return FALSE;

    return nodebt_find(t, t->root, pe);
}

Bool nodebt_find(Tree *t, NodeBT *node, const void *po)
{
    if (!t || !node || !po)
        return FALSE;

    if (t->cmp_element_function(node->info, po) > 0)
        return nodebt_find(t, node->left, po);

    if(t->cmp_element_function(node->info, po) < 0)
        return nodebt_find(t, node->right, po);

    return TRUE;
}