/**
		En este archivo se implementa el codigo que es encargado
	de recrear el concepto filosófico de Pila como Tipo 
	de Dato Abstracto.

		El concepto se construye sobre el TDA Universal, para mantener
	transparencia sobre cualquier TDA, ya que ese es el propósito 
	principal de este TDA Universal

	Vinicio Flores, 2014
	Tecnológico de Costa Rica

**/


#include "tda_stack.h"

void tda_push(tda_stack_t stack, void *data)
{
	tda_base_insf(stack,data);
	if(*stack) tda_set_type(stack,TDA_STACK);
}

void *tda_pop(tda_stack_t stack)
{
	if(!(*stack)) return NULL;
	void *retdat = tda_base_getdata(stack, (*stack)->tda_index);
	tda_base_delete(stack,(*stack)->tda_index);
	return retdat;
}

void tda_stack_destroy(tda_stack_t stack)
{
	int lim = tda_stack_len(stack);
	if(*stack){
		while(lim){
			tda_pop(stack);
			lim--;
		}
	}
}

void tda_stack_show(tda_stack_t stack)
{
	int lim = tda_stack_len(stack);
	if(*stack){
		while(lim){
			printf("%d\n",     *((int *) tda_base_getdata(stack,lim) ));
			lim--;
		}
	}
}

int tda_stack_isempty(tda_stack_t stack) { return tda_base_isempty(stack); }
int tda_stack_len(tda_stack_t stack){ return tda_base_len(stack); }

