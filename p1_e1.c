#include "node.h"

 int main(){
    Node *n1, *n2;
    char * cadena1, * cadena2;

    n1 = nodeIni(111, "first");
    n2 = nodeIni(222, "second");

    printf("%s%s\n",(cadena1 = nodePrintAll(n1)), (cadena2 = nodePrintAll(n2)));

    free(cadena1);
    free(cadena2);

    printf("Son iguales? %s\n", nodeEquals(n1, n2) != 0 ? "No" : "Si" );

    printf("Id primer nodo: %d\n", n1 -> id);

    printf("Nombre del segundo nodo es: %s\n", n2 -> name);

    nodeCopy(n1,n2);

    printf("%s%s\n",(cadena1 = nodePrint(n1)), (cadena2 = nodePrint(n2)));

    free(cadena1);
    free(cadena2);

    printf("Son iguales? %s\n", nodeEquals(n1, n2) != 0 ? "No" : "Si" );

    nodeFree(n1);
    nodeFree(n2);

    return 0;
}