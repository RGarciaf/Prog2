#include "stack_fp.h"
#include "graph.h"
#include "node.h"

 int main(int argc, char ** argv){
    Graph * g = graph_ini();
    FILE * f = fopen("inputs/g2_s.txt", "r");
    Node * n1, * n2;
    Stack * s = NULL;

    if(!f || !g)
        return -1;

    graph_readFromFile(f,g);

    n1 = graph_getNode(g, 1);
    n2 = graph_getNode(g, 124);

    s = graph_findDeepSearch_getPath(g, n1, n2);

    stack_print(stdout, s);

    node_destroy(n1);
    node_destroy(n2);

    graph_destroy(g);
    stack_destroy(s);

    fclose(f);

    return 0;
}