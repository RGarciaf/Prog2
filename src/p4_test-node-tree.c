#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "node.h"
#include "int.h"
#include "types.h"

#define MAX_LINE 350
#define MAX 300

int main(int argc, char const *argv[])
{
	FILE *f_in;
	char buff[MAX_LINE], name[MAX];
	int id;
	Tree *t;
	Node * n;

	if (argc != 2)
	{
		printf("uso: %s <archivo>", argv[0]);
		return -1;
	}

	t = tree_ini((destroy_element_function_type) node_destroy, (copy_element_function_type) node_copy, (print_element_function_type) nodeTree_print, (cmp_element_function_type) node_cmp);

	f_in = fopen(argv[1], "r");

	while (fgets(buff, MAX_LINE, f_in) != NULL)
	{		
		if (sscanf(buff, "%d %s", &id, name) == 2)
		{
			n = node_ini();
			node_setId(n, id);
			node_setName(n, name);
			tree_insert(t, (void *)n);
			node_destroy(n);
		}
	}

	printf("Orden previo:");
	tree_preOrder(stdout,t);
	printf("\nOrden medio:");
	tree_inOrder(stdout, t);
	printf("\nOrden posterior:");
	tree_postOrder(stdout, t);

	printf("\nNumero de nodos: %d\n", tree_numNodes(t));
	printf("Profundidad: %d\n", tree_depth(t));

	fclose(f_in);

	tree_free(t);

	return 0;
}
