#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct _Node {
    char name[MAX];
    int id;
    int nConnector;
};

typedef struct _Node Node;

Node * nodeIni(int id, char * name);

int nodeEquals(Node * n1, Node * n2 );

Node * nodeCopy(Node * n1, Node * n2);

char * nodePrintAll(Node * node);

char * nodePrint(Node * node); 

void nodeFree(Node * node);

#endif