#include "stack_elestack.h"

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
        stack_push(s, ele);
    }

    EleStack_destroy(ele);

    return OK;
}

double media(Stack * s){
    Stack * stackaux = stack_ini();;
    double media;
    int * info = NULL;
    EleStack * eleaux = NULL;

    while(stack_isEmpty(s) == FALSE){
        eleaux = stack_pop(s);
        info = (int *) EleStack_getInfo(eleaux);

        media += *info;

        stack_push(stackaux, eleaux);
        EleStack_destroy(eleaux);
        free(info);
    }

    while(stack_isEmpty(stackaux) == FALSE){
        eleaux = stack_pop(stackaux);
        stack_push(s, eleaux);
        EleStack_destroy(eleaux);
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

    s = stack_ini();

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