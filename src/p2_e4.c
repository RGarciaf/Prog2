#include "stack_fp.h"
#include "graph.h"
#include "node.h"

 int main(int argc, char ** argv){
    Graph * g = graph_ini();
    FILE * f = fopen("inputs/g2_s.txt", "r");
    Node * n1, * n2, *naux;

    if(!f || !g)
        return -1;

    graph_readFromFile(f,g);

    n1 = graph_getNode(g, 1);
    n2 = graph_getNode(g, 3);

    if(!(naux = graph_findDeepSearch(g, n1, n2))){
        printf("No hay camino\n");
    } else {
        printf("Se ha encontrado camino\n");
        node_destroy(naux);
    }

    node_destroy(n1);
    node_destroy(n2);

    graph_destroy(g);

    fclose(f);

    return 0;
}