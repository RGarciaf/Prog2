#include "graph.h"
#include "types.h"

 int main(){
    Node *n1, *n2;
    Graph * g;
    int id1 = 111 , id2=222;

    n1 = nodeIni(id1, "first");
    n2 = nodeIni(id2, "second");

    g = graph_ini();

    printf("Insertando nodo 1...resultado...:%d\n", graph_insertNode(g,n1));
    printf("Insertando nodo 2...resultado...:%d\n", graph_insertNode(g,n2));

    graph_insertEdge(g,id1, id2);
    printf("Insertando edge: nodo2 --> nodo 1\n");

    printf("Conectados nodo 1 y nodo 2? %s\n", graph_areConnected(g,id1, id2) == TRUE ? "Si" : "No");
    printf("Conectados nodo 2 y nodo 1? %s\n", graph_areConnected(g,id2, id1) == TRUE ? "Si" : "No");

    printf("Insertando nodo 2...resultado...:%d\n", graph_insertNode(g,n2));

    graph_print( stdout, g);

    node_destroy(n1);
    node_destroy(n2);

    graph_destroy(g);

    return 0;
}