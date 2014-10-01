#ifndef __TDA_U_H
#define __TDA_U_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TDA_SIMPLE_LIST		1
#define TDA_DOUBLE_LIST		2
#define TDA_CSIMPLE_LIST  	3
#define TDA_CDOUBLE_LIST	4
#define TDA_STACK			5

#define TDA_STD_INDEX_START 1

#define SAVE_REFPTR			-3
#define SAVE_BUFFER 		-4

#define INVALID_INSERTION	-5
#define MAX_STATIC_STACK_LIM 1024

typedef struct tda_node
{
	int tda_index;
	void *tda_data;
	struct tda_node *tda_next;
	struct tda_node *tda_last;
} tda_base_t;

/* Implementamos la pila estatica por aparte, la dinamica se
  * implementa con el tda base */
typedef struct tda_static_stack
{
	int sp;
	int bp;
	void *stack[MAX_STATIC_STACK_LIM];
} tda_static_stack_t;


/* Aliases de los diferentes tipos de TDA soportados
	* al fin y al cabo, todos son un tda_base_t por debajo */
typedef tda_base_t tda_simple_list_t;
typedef tda_base_t tda_double_list_t;
typedef tda_base_t tda_circle_list_t;
typedef tda_base_t tda_double_circle_list_t;
typedef tda_base_t tda_stack_t;
typedef tda_stack_t tda_dinamic_stack_t;

typedef enum  {false, true} bool;

tda_base_t *tda_base_node(void *);
tda_base_t *tda_base_search(tda_base_t**,int,int);

void tda_base_free(tda_base_t*);
void tda_base_show(tda_base_t **, int);
void tda_base_new(tda_base_t **,void *, int);
int tda_base_add(tda_base_t **, void *, int);
int tda_base_ins(tda_base_t **, void *, int, int);
void tda_base_insf(tda_base_t **, void *, int);
void tda_base_save_buffered(tda_base_t **, void *, int size, int index,int);
void tda_base_save_reference(tda_base_t **, void *, int index,int);
void tda_base_delete(tda_base_t **, int index, int);
void tda_base_save(tda_base_t **, void *, int,int index, int savetype, int);
void tda_base_index(tda_base_t **,tda_base_t * ,int);

/* Funciones de trabajo con pilas */
void tda_push(tda_base_t **, void *,int,int);
void *tda_spop(tda_base_t **,int,int);
void *tda_pop(tda_base_t **,int,int);

#endif 

