#ifndef __TDA_CORE_H
#define __TDA_CORE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TDA_INIT_INDEX		0

typedef enum { TDA_BASE, TDA_SIMPLE_LIST, TDA_CIRCULAR_LIST, TDA_STACK, TDA_TAIL, TDA_DOUBLE_TAIL } tda_type_t;
/* La base de gran parte de los TDA más complejos es la lista doblemente enlazada */
typedef struct double_linked_list
{
	tda_type_t tda_type;
	int tda_index;  
	short dataCopied; //si malloc es usado para "copiar" informacion
	void *tda_data;
	struct double_linked_list *tda_next;
	struct double_linked_list *tda_last;

} tda_base_t;
/* Funciones de implementación del tda base */
void tda_set_indexes(tda_base_t**);
void tda_base_new  (tda_base_t**,void*);			/* Crea una nueva lista */
void tda_base_nnewmake (tda_base_t**,int n); 		/* Crea una lista con 'n' cantidad de nodos iniciales */
int  tda_base_insf (tda_base_t**,void*);			/* Agrega un nodo al principio de la lista */
int  tda_base_ins  (tda_base_t**,int,void*);		/* Inserta un elemento despues del nodo con index = i */
int  tda_base_add  (tda_base_t**,void*);			/* Agrega un elemento al final de la lista */
int tda_base_add_copy (tda_base_t**, void*);		/* Reserva memoria para hacer una copia del dato y agrega la referencia */
void tda_base_show (tda_base_t**);					/* Imprima a stdout información de cada nodo */
void tda_base_setdata(tda_base_t**,void*,int i);	/* Guarda un dato en el nodo de indice i */
void tda_base_delete(tda_base_t**,int);				/* Elimina un elemento de indice i */
void tda_base_destroy(tda_base_t**);				/* Destruye una lista enlazada completamente (libera todos los nodos de la memoria) */
void *tda_base_getdata(tda_base_t**,int i);			/* Obtiene el puntero del dato guardado en el nodo de indice i */
void tda_set_type(tda_base_t**,tda_type_t);			/* Convierte la lista estándar (doblemente enlazada) en el tipo especificado */
int tda_get_end(tda_base_t **);						/* Retorna el indice del ultimo elemento de la lista */
void tda_base_reverseElements(tda_base_t **head);   /* Reversa el orden de los punteros datos en la lista */


tda_base_t *tda_base_search(tda_base_t**,int i);	/* Devuelve un puntero a nodo con indice igual a i(arg2) */

#endif
