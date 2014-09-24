#ifndef __TDA_CORE_H
#define __TDA_CORE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TDA_INIT_INDEX		1

<<<<<<< HEAD
/* Tipos de TDA soportados por este TDA Universal */
typedef enum { TDA_BASE, TDA_SIMPLE_LIST, TDA_CIRCULAR_LIST, TDA_DOUBLE_CIRCULAR_LIST, TDA_STACK, TDA_TAIL, TDA_DOUBLE_TAIL } tda_type_t;

#define TDA_DOUBLE_LIST TDA_BASE
#define TDA_STD 		TDA_BASE


/* Códigos para retornar errores */
#define TDA_ERR_INVALID_INSERTION 	 -800
#define TDA_ERR_INVALID_DELETION 	 -801
#define TDA_ERR_INVALID_DATA		 -802

=======
typedef enum { TDA_BASE, TDA_SIMPLE_LIST, TDA_CIRCULAR_LIST, TDA_STACK, TDA_TAIL, TDA_DOUBLE_TAIL } tda_type_t;
>>>>>>> origin/master
/* La base de gran parte de los TDA más complejos es la lista doblemente enlazada */
typedef struct list_d
{
<<<<<<< HEAD
	tda_type_t tda_type;		/* Define el tipo de TDA 	 				     */
	int tda_index;				/* Guarda el indice del nodo 					 */
	void *tda_data;				/* Puntero a algún dato a guardar por referencia */
	struct list_d *tda_next;	/* Puntero al siguiente nodo 					*/
	struct list_d *tda_last;	/* Puntero al nodo anterior (si es necesario)    */
=======
	tda_type_t tda_type;
	int tda_index;
	short dataCopied; //si malloc es usado para "copiar" informacion
	void *tda_data;
	struct double_linked_list *tda_next;
	struct double_linked_list *tda_last;
>>>>>>> origin/master

} tda_base_t;

typedef tda_base_t *tda_base_p;
/* Define los alias de las distintas modalidades de TDA soportadas */
typedef tda_base_t tda_simple_list_t;
typedef tda_base_t tda_double_list_t;
typedef tda_base_t tda_simple_circle_list_t;
typedef tda_base_t tda_double_circle_list_t;

typedef tda_base_p tda_simple_list_p;
typedef tda_base_p tda_double_list_p;
typedef tda_base_p tda_simple_circle_list_p;
typedef tda_base_p tda_double_circle_list_p;

/* Definimos mi valor booleano ;-) */
typedef enum {false, true} bool;
/* Definimos un tipo de cadena */
typedef char* String;

/* Funciones de implementación del tda base */
<<<<<<< HEAD

void tda_base_savedat(tda_base_t**,void*,int,size_t);					/* Guarda en un buffer apuntador por data un dato */
void tda_set_indexes(tda_base_t**);										/* Re-coloca los indices de los nodos de una lista */
int  tda_base_insf (tda_base_t**,void*);								/* Agrega un nodo al principio de la lista */
int  tda_base_ins  (tda_base_t**,int,void*);							/* Inserta un elemento despues del nodo con index = i */
int  tda_base_add  (tda_base_t**,void*);								/* Agrega un elemento al final de la lista */
void tda_base_add_all(tda_base_t**dest,tda_base_t**src);				/* Agrega todos los elementos de src en dest */
void tda_base_nnew (tda_base_t**,int n); 								/* Crea una lista con 'n' cantidad de nodos iniciales */
void tda_base_show (tda_base_t**);										/* Imprima a stdout información de cada nodo */
void tda_base_setdata(tda_base_t**,void*,int i);						/* Guarda un dato en el nodo de indice i */
void tda_base_delete(tda_base_t**,int);									/* Elimina un elemento de indice i */
void tda_base_destroy(tda_base_t**);									/* Destruye una lista enlazada completamente (libera todos los nodos de la memoria) */
void *tda_base_getdata(tda_base_t**,int i);								/* Obtiene el puntero del dato guardado en el nodo de indice i */
void tda_set_type(tda_base_t**,tda_type_t);								/* Convierte la lista estándar (doblemente enlazada) en el tipo especificado */
void tda_base_del(tda_base_t**,tda_base_t**);							/* Saca un nodo de la lista */
void tda_print_type(tda_base_t **head);									/* Imprime en terminal el tipo de TDA */
int tda_get_end(tda_base_t**);											/* Retorna el indice del ultimo elemento de la lista */
int tda_base_len(tda_base_t**);											/* Obtiene el numero de nodos de una lista */
bool tda_base_isempty(tda_base_t**);									/* Verifica si la lista está vacía o no */

tda_base_t *tda_get_head(tda_base_t**);									/* Devuelve la cabeza utilizable de una lista, no la nula (que guarda el tipo de TDA) */
tda_base_t *tda_base_node(void *pData);									/* Aloja un nuevo nodo en la memoria con el dato indicado */
tda_base_t *tda_base_search(tda_base_t**,int i);						/* Devuelve un puntero a nodo con indice igual a i(arg2) */
=======
void tda_set_indexes(tda_base_t**);
void tda_base_new  (tda_base_t**,void*);			/* Crea una nueva lista */
int  tda_base_insf (tda_base_t**,void*);			/* Agrega un nodo al principio de la lista */
int  tda_base_ins  (tda_base_t**,int,void*);		/* Inserta un elemento despues del nodo con index = i */
int  tda_base_add  (tda_base_t**,void*);			/* Agrega un elemento al final de la lista */
int tda_base_add_copy (tda_base_t**, void*);		/* Reserva memoria para hacer una copia del dato */
void tda_base_nnew (tda_base_t**,int n); 			/* Crea una lista con 'n' cantidad de nodos iniciales */
void tda_base_show (tda_base_t**);					/* Imprima a stdout información de cada nodo */
void tda_base_setdata(tda_base_t**,void*,int i);	/* Guarda un dato en el nodo de indice i */
void tda_base_delete(tda_base_t**,int);				/* Elimina un elemento de indice i */
void tda_base_destroy(tda_base_t**);				/* Destruye una lista enlazada completamente (libera todos los nodos de la memoria) */
void *tda_base_getdata(tda_base_t**,int i);			/* Obtiene el puntero del dato guardado en el nodo de indice i */
void tda_set_type(tda_base_t**,tda_type_t);			/* Convierte la lista estándar (doblemente enlazada) en el tipo especificado */
int tda_get_end(tda_base_t **);						/* Retorna el indice del ultimo elemento de la lista */

tda_base_t *tda_base_search(tda_base_t**,int i);	/* Devuelve un puntero a nodo con indice igual a i(arg2) */
>>>>>>> origin/master

#endif
