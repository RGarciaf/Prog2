#include "queue.h"
#include "graph.h"
#include "node.h"
#include "list.h"
#include "int.h"
#include <stdio.h>
#include <stdlib.h>

 int main(int argc, char ** argv){
   List * l1 = list_ini(free, int_copy, int_print, int_cmp );
   List * l2 = list_ini(free, int_copy, int_print, int_cmp );
    int i;

    if(argc != 2){
        printf("Formato: %s <numero>\n", argv[0]);
        return -1;
    }
   
    for(i = 0; i < atoi(argv[1]); i++){
        if(i%2 == 0){
            list_insertFirst(l1, &i);
        } else {
            list_insertLast(l1, &i);
        }
        list_insertInOrder(l2, &i);
    }

    list_print(stdout, l1);
    list_print(stdout, l2);

    list_destroy(l1);
    list_destroy(l2);

    return 0;
}