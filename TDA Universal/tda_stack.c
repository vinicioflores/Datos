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
	while(lim){
		tda_pop(stack);
		lim--;
	}
}

int tda_stack_isempty(tda_stack_t stack)
{
	return *stack == NULL;
}

int tda_stack_len(tda_stack_t stack)
{
	return tda_base_len(stack);
}

