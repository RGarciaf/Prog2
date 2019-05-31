#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "str.h"
#include "types.h"

#define MAX_LINE 350
#define MAX 300

int main(int argc, char const *argv[])
{
	FILE *f_in;
	char buff[MAX_LINE];
	char id[MAX_LINE];
	Tree *t;
    void * ret;

	if (argc != 2)
	{
		printf("uso: %s <archivo>", argv[0]);
		return -1;
	}

	t = tree_ini(string_destroy, string_copy, string_print_tree, string_cmp);

	f_in = fopen(argv[1], "r");

	while (fgets(buff, MAX_LINE, f_in) != NULL)
	{
		if (sscanf(buff, "%s", id) == 1)
		{
			tree_insert(t, (void *)&id);
		}
	}

	
	printf("\nOrden medio:");
	tree_inOrder(stdout, t);

	printf("\nNumero de nodos: %d\n", tree_numNodes(t));
	printf("Profundidad: %d\n", tree_depth(t));

	printf("Introduzca un numero: ");
	scanf("%s", id);

	if ((ret = tree_inorder_predecesor(t, (void*)&id)) != NULL){
    }else
		printf("El dato o su antecesor NO se encuentra dentro del Arbol\n");

	fclose(f_in);

	tree_free(t);

	return 0;
}
