/******************************************************************************

Nombre del modulo: node.c

Descripci�n: Modulo que define y da acceso a la estructura de datos node.

Autor: Roman Garcia

Fecha: 06-02-2019

******************************************************************************/

/*=== Cabeceras =============================================================*/
#include "node.h"

/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: nodeIni

Descripcion: Crea e inicializa un node

Retorno: 
- El nodo creado, si se ha terminado sin problemas
- null, en cualquier otro caso.

-----------------------------------------------------------------------------*/

Node * nodeIni(int id, char * name) {
    Node * n = (Node *) malloc (sizeof (Node));

    if(!n) {
        return NULL;
    }
    
    n -> id = id;
    n -> nConnector = 0;
    strcpy(n->name, name);

    return n;
}

int nodeEquals(Node * n1, Node * n2 ) {
    return n1 ->id == n2 ->id && strcmp(n1->name, n2->name);
}

Node * nodeCopy(Node * n1, Node * n2){
    n2 -> id = n1 -> id;
    strcpy(n2->name, n1 -> name);
    return n2;
}

char * nodePrintAll(Node * node){
    char * ret = (char *) malloc (sizeof(char) * MAX);
    sprintf(ret, "[%d, %s, %d]",node -> id, node -> name, node -> nConnector );
    return ret;
}

char * nodePrint(Node * node){
    char * ret = (char *) malloc (sizeof(char) * MAX);
    sprintf(ret, "[%d, %s]",node -> id, node -> name );
    return ret;
}

void nodeFree(Node * node){
    free(node);
}