/******************************************************************************

Nombre del modulo: node.c

Descripcion: Modulo que define y da acceso a la estructura de datos node.

Autor: Roman Garcia

Fecha: 06-02-2019

******************************************************************************/

/*=== Cabeceras =============================================================*/
#include "node.h"
#define NAME_L 64

struct _Node
{
    char name[MAX];
    int id;
    int nConnect;

    Label etq;
    int antecesor_id;
};

int abs(int n);

/*=== Funciones =============================================================*/

Node *node_ini()
{
    Node *n = (Node *)malloc(sizeof(Node));

    if (!n)
    {
        return NULL;
    }

    n->id = 0;
    n->nConnect = 0;
    n->antecesor_id = -1;
    n->etq = BLANCO;

    return n;
}

void node_destroy(Node *n)
{
    free(n);
}

int node_getId(const Node *n)
{
    return n->id;
}

char *node_getName(const Node *n)
{
    char *cadena = (char *)malloc(sizeof(char) * MAX);
    strcpy(cadena, n->name);

    return cadena;
}

int node_getConnect(const Node *n)
{
    return n->nConnect;
}

Label node_getEtiqueta(const Node *n)
{
    return n->etq;
}

Node *node_setEtiqueta(Node *n, Label etq)
{
    n->etq = etq;
    return n;
}

Label node_getAntecesor(const Node *n)
{
    return n->antecesor_id;
}

Node *node_setAntecesor(Node *n, int antecesor_id)
{
    n->antecesor_id = antecesor_id;
    return n;
}

Node *node_setId(Node *n, const int id)
{
    n->id = id;

    return n;
}

Node *node_setName(Node *n, const char *name)
{
    strcpy(n->name, name);

    return n;
}

Node *node_setConnect(Node *n, const int cn)
{
    n->nConnect = cn;

    return n;
}

int node_cmp(const Node *n1, const Node *n2)
{
    if(n1->id == n2->id)
        return strcmp(n1->name, n2->name);

    return n1->id - n2->id;
}

int abs(int n)
{
    if (n < 0)
        return n * -1;
    return n;
}

Node *node_copy(const Node *n1)
{
    Node *n2;

    if (!n1)
    {
        return NULL;
    }

    n2 = node_ini();

    if (!n2)
        return NULL;

    n2->id = n1->id;
    n2->antecesor_id = n1->antecesor_id;
    n2->etq = n1->etq;
    n2->nConnect = n1->nConnect;
    strcpy(n2->name, n1->name);
    return n2;
}

int node_print(FILE *pf, const Node *node)
{

    if (!pf || !node)
        return -1;

    return fprintf(pf, "[%d, %s, %d] ", node->id, node->name, node->nConnect);
}

int nodeTree_print(FILE *pf, const Node *node)
{

    if (!pf || !node)
        return -1;

    return fprintf(pf, "[%d, %s] ", node->id, node->name);
}

Node *nodeIni(int id, char *name)
{
    Node *n = (Node *)malloc(sizeof(Node));

    if (!n)
    {
        return NULL;
    }

    n->id = id;
    n->nConnect = 0;
    strcpy(n->name, name);

    return n;
}

Node *nodeCopy(Node *n1, Node *n2)
{
    n2->id = n1->id;
    strcpy(n2->name, n1->name);
    return n2;
}

char *nodePrint(Node *node)
{
    char *ret = (char *)malloc(sizeof(char) * MAX);
    sprintf(ret, "[%d, %s]", node->id, node->name);
    return ret;
}

char *nodePrintAll(Node *node)
{
    char *ret = (char *)malloc(sizeof(char) * MAX);
    sprintf(ret, "[%d, %s, %d]", node->id, node->name, node->nConnect);
    return ret;
}