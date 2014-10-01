#include "tda_u.h"

tda_base_t *tda_base_node(void *dataptr)
{
	tda_base_t *newnode = (tda_base_t *) malloc (sizeof(tda_base_t));
	
	newnode->tda_next = NULL;
	newnode->tda_last = NULL;
	newnode->tda_data = dataptr;
	return newnode;
}

void tda_base_free(tda_base_t *node)
{
	if(!node) return;
	if(node->tda_data) free(node->tda_data);
	free(node);
	node = NULL;
}

void tda_base_new(tda_base_t **head, void *pdata, int tda_type)
{
	if(!(*head)){
		*head = tda_base_node(pdata);
		(*head)->tda_data = pdata;
		switch(tda_type){
			case TDA_STACK:
			case TDA_SIMPLE_LIST:
			case TDA_DOUBLE_LIST:
				(*head)->tda_next = (*head)->tda_last = NULL;
				break;
			case TDA_CSIMPLE_LIST:
				(*head)->tda_next = *head;
				break;
			case TDA_CDOUBLE_LIST:
				(*head)->tda_next = *head;
				(*head)->tda_last = *head;
				break;
		}
		tda_base_index(head,NULL,tda_type);
	}
}

int tda_base_add(tda_base_t **head, void *pdata, int tda_type)
{
	tda_base_t *newnode = tda_base_node(pdata);
	tda_base_t *ip = *head;

	if(!ip){  tda_base_new(head,pdata,tda_type); return 1; }
	bool condition=(tda_type==TDA_SIMPLE_LIST || tda_type==TDA_DOUBLE_LIST) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);

	for(;condition;){
		condition = (tda_type==TDA_SIMPLE_LIST || tda_type==TDA_DOUBLE_LIST) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);
		if(condition) ip = ip->tda_next;
	}

	if(ip){ 
			if(tda_type == TDA_CSIMPLE_LIST || tda_type == TDA_CDOUBLE_LIST) newnode->tda_next = ip->tda_next;
			if(tda_type == TDA_DOUBLE_LIST || tda_type == TDA_CDOUBLE_LIST){
				newnode->tda_last = ip;
			}

			ip->tda_next = newnode;
			tda_base_index(head,ip,tda_type);
			if(tda_type == TDA_CDOUBLE_LIST){
				(*head)->tda_last = ip->tda_next;
			}
			return ip->tda_next->tda_index;
		}
	return 0;
}

void tda_base_insf(tda_base_t **head, void *pdata, int tda_type)
{
	tda_base_t *newnode = tda_base_node(pdata);
	tda_base_t *ip = *head;

	if(!ip) tda_base_new(head,pdata,tda_type);
	else {
		bool condition=(tda_type==TDA_SIMPLE_LIST || tda_type==TDA_DOUBLE_LIST || tda_type==TDA_STACK) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);

		for(;condition;){
			condition = condition = (tda_type==TDA_SIMPLE_LIST || tda_type==TDA_DOUBLE_LIST || tda_type==TDA_STACK) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);
			if(condition) ip = ip->tda_next;
		}
		
		newnode->tda_next = *head;

		if(tda_type == TDA_DOUBLE_LIST || tda_type == TDA_CDOUBLE_LIST)
			newnode->tda_last = (*head)->tda_last;
		if(tda_type == TDA_CSIMPLE_LIST || tda_type == TDA_CDOUBLE_LIST) ip->tda_next = newnode;
		*head = newnode;
		tda_base_index(head,newnode->tda_last,tda_type);
	} 
}

int tda_base_ins(tda_base_t **head, void *pdata, int index, int tda_type)
{
	if(tda_type == TDA_STACK) return INVALID_INSERTION;
	if(!(*head) && !index) tda_base_new(head,pdata,tda_type);
	else {
		tda_base_t *vecino = tda_base_search(head,index,tda_type);
		if(!(*head) && index) return INVALID_INSERTION;
		else if(!index){ tda_base_insf(head,pdata,tda_type); return TDA_STD_INDEX_START; }
		else if(!vecino->tda_next) return tda_base_add(head,pdata,tda_type);
		else {
			tda_base_t *newnode = tda_base_node(pdata);
			newnode->tda_next = vecino->tda_next;
			if(tda_type == TDA_DOUBLE_LIST || tda_type == TDA_CDOUBLE_LIST)
				newnode->tda_last = vecino;
			vecino->tda_next = newnode;
			tda_base_index(head,vecino->tda_last,tda_type);
			return vecino->tda_next->tda_index;
		}
	}
	return 0;
}

void tda_base_delete(tda_base_t **head, int index, int tda_type)
{
	if(!(*head)) return;
	else {
		tda_base_t *last = tda_base_search(head,index-1,tda_type);
		tda_base_t *p = tda_base_search(head,index,tda_type);
		tda_base_t *next = tda_base_search(head,index+1,tda_type);

		if(!p) return;

		if(p == *head) *head = next;
		if(last) last->tda_next = p->tda_next;
		if(tda_type == TDA_DOUBLE_LIST || tda_type == TDA_CDOUBLE_LIST)
			if(next) next->tda_last = p->tda_last;		
		if(p){
			tda_base_free(p);
			tda_base_index(head,last,tda_type);
		}
	}
}

void tda_base_show(tda_base_t **head, int tda_type)
{
	tda_base_t *ip = *head;
	if(!ip) return;

	bool condition=( (tda_type==TDA_SIMPLE_LIST) || (tda_type==TDA_DOUBLE_LIST) || (tda_type==TDA_STACK) ) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);

	while(condition){
		condition=( (tda_type==TDA_SIMPLE_LIST) || (tda_type==TDA_DOUBLE_LIST) || (tda_type==TDA_STACK) ) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);
		if(ip) printf("[%3d] #node#{0x%x}, #nextnode#{0x%x}, #lastnode#{0x%x}, #dataptr#{0x%x}(%c) \n",
			ip->tda_index,ip,ip->tda_next,ip->tda_last,ip->tda_data, *((char *)ip->tda_data) );
		if(condition) ip = ip->tda_next;
	}	
}


void tda_base_index(tda_base_t **head, tda_base_t *lastc, int tda_type)
{
	int k = TDA_STD_INDEX_START;
	tda_base_t *ip = *head, *last = lastc;

	if(!(*head)) return;

	bool condition=( (tda_type==TDA_SIMPLE_LIST || tda_type==TDA_DOUBLE_LIST || tda_type==TDA_STACK) ) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);

	while(condition && ip){
		if(ip)  condition=( (tda_type==TDA_SIMPLE_LIST || tda_type==TDA_DOUBLE_LIST || tda_type==TDA_STACK) ) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);
		else break;

		ip->tda_index = k;
		if(tda_type == TDA_CDOUBLE_LIST){
			ip->tda_last = last;
			last = ip;
		}


		if(condition) ip = ip->tda_next;
		k++;
	}
}


tda_base_t *tda_base_search(tda_base_t **head, int index, int tda_type)
{
	tda_base_t *ip = *head;
	bool condition=(tda_type==TDA_SIMPLE_LIST || tda_type==TDA_DOUBLE_LIST || tda_type==TDA_STACK) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);

	while(condition==true){
		condition=(tda_type==TDA_SIMPLE_LIST || tda_type==TDA_DOUBLE_LIST || tda_type==TDA_STACK) ?  (ip->tda_next != NULL) : (ip->tda_next != *head);
		if(ip->tda_index == index) return ip;
		ip = ip->tda_next;
	}	
	return NULL;
}

void tda_base_save_reference(tda_base_t **head, void *pdata, int index, int tda_type)
{
	tda_base_t *dest = tda_base_search(head,index,tda_type);
	if(dest) dest->tda_data = pdata;
	return;
}

void tda_base_save_buffered(tda_base_t **head, void *pdata, int size, int index, int tda_type)
{
	tda_base_t *dest = tda_base_search(head,index,tda_type);
	if(dest){ 
		dest->tda_data = malloc(size);
		memcpy(dest->tda_data, pdata, size);
	}
	return;
}

void tda_base_save(tda_base_t **head, void *pdata, int size, int index, int savetype, int tda_type)
{
	switch(savetype){
		case SAVE_REFPTR:
			tda_base_save_reference(head,pdata,index,tda_type);
			break;
		case SAVE_BUFFER:
			tda_base_save_buffered(head,pdata,size,index,tda_type);
			break;
	}
}

/*** Operaciones con TDA Pila ****/


// Inserta un elemento en el tope de la pila
void tda_push(tda_base_t **head, void *pdata, int size, int tda_type)
{
	if(tda_type != TDA_STACK) return;
	else {
		tda_base_insf(head,NULL,TDA_STACK);
		tda_base_t *dest = *head;
		dest->tda_data = malloc (size);
		memcpy(dest->tda_data,pdata,size);
	}
}

// Extrae el dato del elemento del tope de la pila, sin quitar dicho
// elemento de la pila (soft pop)
void *tda_spop(tda_base_t **head, int size, int tda_type)
{
	tda_base_t *top = tda_base_search(head,TDA_STD_INDEX_START,TDA_STACK);
	void *retval = malloc(size);
	memcpy(retval,top->tda_data,size);
	return retval;
}

// Extrae un elemento desde el tope de la pila
void *tda_pop(tda_base_t **head, int size, int tda_type)
{
	if(tda_type != TDA_STACK) return NULL;
	else {
		void *retval = tda_spop(head,size,TDA_STACK);
		tda_base_delete(head,TDA_STD_INDEX_START,TDA_STACK);
		return retval;
	}
}



