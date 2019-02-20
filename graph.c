#include "graph.h"

Graph *graph_ini() {

}

void graph_destroy(Graph *g) {

}

Status graph_insertNode(Graph *g, const Node *n)
{
}

Status graph_insertEdge(Graph *g, const int nId1, const int nId2) {

}

Node *graph_getNode(const Graph *g, int nId) {

}

Status graph_setNode(Graph *g, const Node *n) {

}

int *graph_getNodesId(const Graph *g)  {

}

int graph_getNumberOfNodes(const Graph *g)  {

}

int graph_getNumberOfEdges(const Graph *g) { 

}

Bool graph_areConnected(const Graph *g, const int nId1, const int nId2) {

}

int graph_getNumberOfConnectionsFrom(const Graph *g, const int fromId)  {

}

int *graph_getConnectionsFrom(const Graph *g, const int fromId) { 

}

int graph_print(FILE *pf, const Graph *g) {

}

Status graph_readFromFile(FILE *fin, Graph *g)
{
}

int find_node_index(const Graph *g, int nId1)
{
    int i;
    if (!g)
        return -1;

    for (i = 0; i < g->num_nodes; i++)
    {
        if (node_getId(g->nodes[i]) == nId1)
            return i;
    }

    // ID not find
    return -1;
}

int *graph_getConectionsIndex(const Graph *g, int index)
{
    int *array = NULL, i, j = 0, size;

    if (!g)
        return NULL;
    if (index < 0 || index > g->num_nodes)
        return NULL;
    // get memory for the array with the connected nodes index
    size = node_getConnect(g->nodes[index]);
    array = (int *)malloc(sizeof(int) * size);
    if (!array)
    {
        // print errorr message
        fprintf(stderr, "%s\n", strerror(0));
        return NULL;
    }

    // asigno valores al array con los indices de los nodos conectados
    for (i = 0; i < g->num_nodes; i++)
    {
        if (g->connections[index][i] == TRUE)
        {
            array[j] = i;
            j++;
        }
    }

    return array;
}

Status graph_readFromFile(FILE *fin, Graph *g)
{
    Node *n;
    char buff[MAX_LINE], name[MAX_LINE];
    int i, nnodes = 0, id1, id2;
    Status flag = ERROR;

    // read number of nodes
    if (fgets(buff, MAX_LINE, fin) != NULL)
        if (sscanf(buff, "%d", &nnodes) != 1)
            return ERROR;

    // init buffer_node
    n = node_ini();
    if (!n)
        return ERROR;

    // read nodes line by line
    for (i = 0; i < nnodes; i++)
    {
        if (fgets(buff, MAX_LINE, fin) != NULL)
            if (sscanf(buff, "%d %s", &id1, name) != NO_FILE_POS_VALUES)
                break;

        // set node name and node id
        node_setName(n, name);
        node_setId(n, id1);

        // insert node in the graph
        if (graph_insertNode(g, n) == ERROR)
            break;
    }

    // Check if all node have been inserted
    if (i < nnodes)
    {
        node_destroy(n);
        return ERROR;
    }

    // read connections line by line and insert it
    while (fgets(buff, MAX_LINE, fin))
    {
        if (sscanf(buff, "%d %d", &id1, &id2) == NO_FILE_POS_VALUES)
            if (graph_insertEdge(g, id1, id2) == ERROR)
                break;
    }

    // check end of file
    if (feof(fin))
        flag = OK;

    // clean up, free resources
    node_destroy(n);
    return flag;
}