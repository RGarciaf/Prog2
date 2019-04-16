#ifndef QUEUEL_H
#define QUEUEL_H

#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#define MAXQUEUEL 4096


typedef struct _Queuel Queuel; /* Tipos de los punteros a función soportados por la cola.Nota: podrían estar en elem_functions.h e incluirlo aquí  */                                              

/**------------------------------------------------------------------
 * Inicializa la cola: reserva memoria para ella e inicializa todos sus elementosa NULL.------------------------------------------------------------------*/
Queuel *queuel_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4); 

/**------------------------------------------------------------------
 * Libera la cola, liberandotodos sus elementos.
 * ------------------------------------------------------------------*/
void queuel_destroy(Queuel *q);

/**------------------------------------------------------------------
 * Comprueba si la cola está vacía.
 * ------------------------------------------------------------------*/
Bool queuel_isEmpty(const Queuel *q);

/**------------------------------------------------------------------
 * Comprueba si la cola está llena.
 * ------------------------------------------------------------------*/
Bool queuel_isFull(const Queuel *queuel);

/**------------------------------------------------------------------
 * Inserta un nuevo nodo en la cola, reservando memoria nueva para él y 
 * haciendo una copia del elemento recibido.
 * ------------------------------------------------------------------*/
Status queuel_insert(Queuel *q, const void *pElem);

/**------------------------------------------------------------------
 * Extrae un elemento de la cola. 
 * Devuelve directamente el puntero al elemento (no hace copia).------------------------------------------------------------------*/
void *queuel_extract(Queuel *q);

/**------------------------------------------------------------------
 * Devuelve el número de elementos de la cola.
 * ------------------------------------------------------------------*/
int queuel_size(const Queuel *q);

/**------------------------------------------------------------------
 * Imprime toda la cola, devolviendo el número de caracteres escritos.
 * ------------------------------------------------------------------*/
int queuel_print(FILE *pf, const Queuel *q);

#endif