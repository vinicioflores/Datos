#ifndef __TDA_STACK_H
#define __TDA_STACK_H

#include "tda_core.h"

typedef tda_base_t *tda_stack_p;
typedef tda_base_t **tda_stack_t;

void tda_push(tda_stack_t, void *data);
void *tda_pop(tda_stack_t);
void tda_stack_destroy(tda_stack_t);
int tda_stack_isempty(tda_stack_t);
int tda_stack_len(tda_stack_t);

#endif

