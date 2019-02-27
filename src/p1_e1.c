#include "node.h"
#include "types.h"

 int main(){
    Node *n1, *n2;
    char * cadena1, * cadena2;

    n1 = nodeIni(111, "first");
    n2 = nodeIni(222, "second");

    printf("%s%s\n",(cadena1 = nodePrintAll(n1)), (cadena2 = nodePrintAll(n2)));

    free(cadena1);
    free(cadena2);

    printf("Son iguales? %s\n", node_cmp(n1, n2) != OK ? "No" : "Si");

    printf("Id primer nodo: %d\n", node_getId(n1));

    printf("Nombre del segundo nodo es: %s\n", node_getName(n2));

    node_destroy(n2);

    n2 = node_copy(n1);

    node_print(stdout, n1);
    node_print(stdout, n2);

    printf("\n");

    printf("Son iguales? %s\n", node_cmp(n1, n2) != 0 ? "No" : "Si");

    node_destroy(n1);
    node_destroy(n2);

    return 0;
}