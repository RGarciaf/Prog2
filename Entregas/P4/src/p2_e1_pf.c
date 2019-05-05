#include "stack_fp.h"

int main()
{
    Node *n1, *n2, *nodeaux;
    Stack *s1;

    n1 = nodeIni(111, "first");
    n2 = nodeIni(222, "second");

    s1 = stack_ini((P_stack_ele_destroy ) node_destroy, (P_stack_ele_copy ) node_copy,(P_stack_ele_print ) node_print);

    stack_push(s1, n1);
    stack_push(s1, n2);

    printf("Contenido de la pila: \n");
    printf("Caracteres imprimidos: %d\n", stack_print(stdout, s1));

    printf("Vaciando pila. Extracciones:\n");
    while (stack_isEmpty(s1) != TRUE)
    {
        node_print(stdout, (nodeaux = stack_pop(s1)));
        node_destroy(nodeaux);
    }

    printf("\nContenido de la pila despues de vaciar:\n");
    printf("Caracteres imprimidos: %d\n", stack_print(stdout, s1));

    node_destroy(n1);
    node_destroy(n2);

    stack_destroy(s1);

    return 0;
}