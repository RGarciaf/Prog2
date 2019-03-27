#include "graph.h"
#include "stack_fp.h"
#include "node.h"


int graph_getNode_index(Graph *g, int id);

Graph *graph_ini()
{
    Graph *g = (Graph *)malloc(sizeof(Graph));

    g->num_nodes = 0;

    return g;
}

void graph_destroy(Graph *g)
{
    int i;

    if (!g)
    {
        return;
    }

    for (i = 0; i < g->num_nodes; i++)
    {
        node_destroy(g->nodes[i]);
    }

    free(g);
}

Status graph_insertNode(Graph *g, Node *n)
{
    Node *nc, *encontrado = NULL;

    if (!g || !n)
    {
        return ERROR;
    }

    if ((encontrado = graph_getNode(g, node_getId(n))) != NULL)
    {
        node_destroy(encontrado);
        return ERROR;
    }

    if (!(nc = node_copy(n)))
    {
        return ERROR;
    }

    g->nodes[g->num_nodes] = nc;
    g->num_nodes++;

    return OK;
}

Status graph_insertEdge(Graph *g, int nId1, int nId2)
{
    int i, j;

    if (!g)
    {
        return ERROR;
    }

    i = graph_getNode_index(g, nId1);
    j = graph_getNode_index(g, nId2);

    if (i < 0 || j < 0)
    {
        return ERROR;
    }

    g->connections[i][j] = 1;

    node_setConnect(g->nodes[i], node_getConnect(g->nodes[i]) + 1);

    return OK;
}

Node * graph_getNode(Graph *g, int nId)
{
    int i;
    /*Graph gc = *gr;
    Graph * g = &gc;*/
    if (!g)
    {
        return NULL;
    }

    i = graph_getNode_index(g, nId);
    if (i < 0)
    {
        return NULL;
    }

    return node_copy(g->nodes[i]);
}

int graph_getNode_index(Graph *g, int id)
{
    int i;

    for (i = 0; i < g->num_nodes; i++)
    {
        if (node_getId(g->nodes[i]) == id)
        {
            return i;
        }
    }
    return -1;
}

Status graph_setNode(Graph *g, Node *nc)
{
    Node * n1;
    char *name;

    if (!g || !nc)
    {
        return ERROR;
    }

    n1 = g->nodes[graph_getNode_index(g, node_getId(nc))];

    node_setConnect(n1, node_getConnect(nc));
    node_setName(n1, (name = node_getName(nc)));

    free(name);

    return OK;
}

int *graph_getNodesId(Graph *g)
{
    int i;
    int *array = (int *)malloc(sizeof(int) * g->num_nodes);

    if (!array || !g)
        return NULL;

    for (i = 0; i < g->num_nodes; i++)
    {
        array[i] = node_getId(g->nodes[i]);
    }

    return array;
}

int graph_getNumberOfNodes(Graph *g)
{

    if (!g)
    {
        return ERROR;
    }

    return g->num_nodes;
}

int graph_getNumberOfEdges(Graph *g)
{
    int i, j, edges;

    if (!g)
    {
        return ERROR;
    }

    for (i = 0, edges = 0; i < g->num_nodes; i++)
    {
        for (j = 0; j < g->num_nodes; j++)
        {
            edges += g->connections[i][j];
        }
    }

    return edges;
}

Bool graph_areConnected(Graph *g, int nId1, int nId2)
{
    /*Graph gc = *gr;
    Graph * g = &gc;*/

    if (!g)
    {
        return FALSE;
    }

    return g->connections[graph_getNode_index(g, nId1)][graph_getNode_index(g, nId2)];
}

int graph_getNumberOfConnectionsFrom(Graph *gr, int fromId)
{
    int i;
    Graph gc = *gr;
    Graph *g = &gc;

    if (!g)
    {
        return ERROR;
    }

    i = graph_getNode_index(g, fromId);

    /*for (j = 0, edges = 0; j < g->num_nodes; j++)
    {
        edges += g->connections[i][j];
    }*/

    return node_getConnect(g->nodes[i]);
}

int *graph_getConnectionsFrom(Graph *g, int fromId)
{
    int i, j, k, *ids;
    /*Graph gc = *gr;
    Graph * g = &gc;*/

    if (!g)
    {
        return ERROR;
    }

    ids = (int *)malloc(sizeof(int) * node_getConnect(g->nodes[graph_getNode_index(g, fromId)]));

    if (!ids)
    {
        return ERROR;
    }

    i = graph_getNode_index(g, fromId);

    for (j = 0, k = 0; j < g->num_nodes; j++)
    {
        if (g->connections[i][j] == 1)
        {
            ids[k++] = node_getId(g->nodes[j]);
        }
    }

    return ids;
}

int graph_print(FILE *pf, Graph *g)
{
    int i, j, *ids;
    int ret = 0;

    if (!g)
    {
        return ERROR;
    }

    ret += fprintf(pf, " Graph\n");

    for (i = 0; i < g->num_nodes; i++)
    {
        ret += node_print(pf, g->nodes[i]);
        if ((ids = graph_getConnectionsFrom(g, node_getId(g->nodes[i]))))
        {
            for (j = 0; j < node_getConnect(g->nodes[i]); j++)
            {
                ret += fprintf(pf, " %d", ids[j]);
            }
        }
        free(ids);
        ret += fprintf(pf, "\n");
    }
    return ret;
}

int find_node_index(Graph *g, int nId1)
{
    int i;
    if (!g)
        return -1;

    for (i = 0; i < g->num_nodes; i++)
    {
        if (node_getId(g->nodes[i]) == nId1)
            return i;
    }

    return -1;
}

int *graph_getConectionsIndex(Graph *g, int index)
{
    int *array = NULL, i, j = 0, size;

    if (!g)
        return NULL;
    if (index < 0 || index > g->num_nodes)
        return NULL;
    /* get memory for the array with the connected nodes index*/
    size = node_getConnect(g->nodes[index]);
    array = (int *)malloc(sizeof(int) * size);
    if (!array)
    {
        /* print errorr message*/
        fprintf(stderr, "%s\n", strerror(0));
        return NULL;
    }

    /* asigno valores al array con los indices de los nodos conectados */
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

Node *graph_findDeepSearch(Graph *g, Node *v, Node *to)
{
    Stack *s = stack_ini((P_stack_ele_destroy)node_destroy, (P_stack_ele_copy)node_copy, (P_stack_ele_print)node_print);
    Node *n, *naux;
    int id, *ids, i;

    if (!g || !v || !to)
    {
        return NULL;
    }

    stack_push(s, (void *)v);

    while (stack_isEmpty(s) == FALSE)
    {
        n = (Node *)stack_pop(s);

        if (node_getEtiqueta(n) == BLANCO)
        {
            node_setEtiqueta(n, NEGRO);

            for (id = ids[i], ids = graph_getConnectionsFrom(g, node_getId(n)), i = 0; i < node_getConnect(n); i++, id = ids[i])
            {

                if (ids[i] == node_getId(to))
                {
                    free(ids);
                    node_destroy(n);
                    stack_destroy(s);
                    return graph_getNode(g,id);
                }

                naux = graph_getNode(g, id);
                if (node_getEtiqueta(naux) == BLANCO)
                {
                    stack_push(s, (void *)naux);
                }
                node_destroy(naux);
            }
        }

        node_destroy(n);
    }

    stack_destroy(s);

    return NULL;
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