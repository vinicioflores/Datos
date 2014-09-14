#include "tda_stack.h"

void tda_push(tda_stack_t stack, void *data)
{
	tda_base_add(stack,data);
	if(!(*stack)->tda_next && !(*stack)->tda_last) 
		tda_set_type(stack,TDA_STACK);
}

void *tda_pop(tda_stack_t stack)
{
	int endpos = tda_get_end(stack);
	printf("endpos:%d\n",endpos);
	void *retdat = tda_base_getdata(stack,endpos);
	tda_base_delete(stack,endpos);
	return retdat;
}

void tda_stack_destroy(tda_stack_t stack)
{
	tda_base_destroy(stack);
}

