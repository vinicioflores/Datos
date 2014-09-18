#include "tda_stack.h"

void tda_push(tda_stack_t stack, void *data)
{
	tda_base_insf(stack,data);
	if(*stack) tda_set_type(stack,TDA_STACK);
}

void *tda_pop(tda_stack_t stack)
{
	void *retdat = tda_base_getdata(stack, (*stack)->tda_index);
	tda_base_delete(stack, (*stack)->tda_index );
	return retdat;
}

void tda_stack_destroy(tda_stack_t stack)
{
	tda_base_destroy(stack);
}

int tda_stack_isempty(tda_stack_t stack)
{
	return *stack == NULL;
}
