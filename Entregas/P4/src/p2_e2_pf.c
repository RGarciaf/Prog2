#include "stack_fp.h"
#include "elestack.h"

Status comprueba_entrada(int argc, char ** argv){
    
    return argc >= 2 ? OK : ERROR;
}

Status introduce_numeros(Stack * s, int n){
    EleStack * ele = EleStack_ini();
    int i;

    if(!ele){
        return ERROR;
    }

    for(i = 0; i <= n; i++){
        EleStack_setInfo(ele, &i);
        stack_push(s, (void *) ele);
    }

    EleStack_destroy(ele);

    return OK;
}

double media(Stack * s){
    Stack * stackaux = stack_ini((P_stack_ele_destroy ) EleStack_destroy, (P_stack_ele_copy ) EleStack_copy,(P_stack_ele_print ) EleStack_print);
    double media;
    int * info = NULL;
    void * eleaux = NULL;

    while(stack_isEmpty(s) == FALSE){
        eleaux = stack_pop(s);
        info = (int *) EleStack_getInfo((EleStack *)eleaux);

        media += *info;

        stack_push(stackaux, eleaux);
        EleStack_destroy((EleStack *)eleaux);
        free(info);
    }

    while(stack_isEmpty(stackaux) == FALSE){
        eleaux = stack_pop(stackaux);
        stack_push(s, eleaux);
        EleStack_destroy((EleStack *) eleaux);
    }

    stack_destroy(stackaux);

    return media/(double) stack_getNelements(s);
    
}

 int main(int argc, char ** argv){
    Stack *s = NULL ;    

    if(comprueba_entrada(argc, argv) == ERROR){
        printf("Uso: %s <numero>\n", argv[0]);
        return -1;
    }

    s = stack_ini((P_stack_ele_destroy ) EleStack_destroy, (P_stack_ele_copy ) EleStack_copy,(P_stack_ele_print ) EleStack_print);

    if(introduce_numeros(s,atoi(argv[1])) == ERROR) {
        return -1;
    }

    printf("Pila antes de la llamada a la funcion: \n");
    stack_print(stdout, s);

    printf("La media es %f\n",media(s));

    printf("Pila despues de la llamada a la funcion: \n");
    stack_print(stdout, s);

    stack_destroy(s);

    return 0;
}