#include "stack_elestack.h"
#include "types.h"

 int main(){
    Node *n1, *n2;
    EleStack *ele1, *ele2, * eleaux;
    Stack *s1;    

    n1 = nodeIni(111, "first");
    n2 = nodeIni(222, "second");

    ele1 = EleStack_ini();
    ele2 = EleStack_ini();

    s1 = stack_ini();

    EleStack_setInfo(ele1, (void *) n1);
    EleStack_setInfo(ele2, (void *) n2);

    stack_push(s1, ele1);
    stack_push(s1, ele2);
    
    printf("Contenido de la pila: \n");
    printf("Caracteres imprimidos: %d\n", stack_print(stdout, s1));

    printf("Vaciando pila. Extracciones:\n");
    while(stack_isEmpty(s1) != TRUE){
        EleStack_print(stdout, (eleaux = stack_pop(s1)));
        EleStack_destroy(eleaux);
    }

    printf("Contenido de la pila despues de vaciar:\n");
    printf("Caracteres imprimidos: %d\n", stack_print(stdout, s1));

    node_destroy(n1);
    node_destroy(n2);
     
    EleStack_destroy(ele1);
    EleStack_destroy(ele2);
    EleStack_destroy(eleaux);

    stack_destroy(s1);

    return 0;
}