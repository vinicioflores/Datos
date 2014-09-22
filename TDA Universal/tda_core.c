#include "tda_core.h"

void tda_set_indexes(tda_base_t **head)
{
	tda_base_t *tmp = *head;
	int i = 1;

	if((*head)->tda_type != TDA_CIRCULAR_LIST){
		while(tmp){
			tmp->tda_index = i;
			tmp = tmp->tda_next;
			i++;
		}
	} else {
		do {
			tmp->tda_index = i;
			tmp = tmp->tda_next;
			i++;
		} while(tmp->tda_next != *head);
	}
}

void tda_base_nnew(tda_base_t **head, int maxn)
{
	int i;

	for(i=0;i<maxn;i++)
		tda_base_add(head,NULL);

}

tda_base_t *tda_base_node(void *data)
{
	tda_base_t *node = (tda_base_t *) malloc (sizeof(tda_base_t));
	node->tda_data = data;
	node->tda_next = NULL;
	node->tda_last = NULL;
	node->tda_index = TDA_INIT_INDEX;
	tda_set_indexes(&node);
	return node;
}

int tda_base_add(tda_base_t **head, void *data)
{
	tda_base_t *tmp=NULL;
	int index = 0;
	if(!(*head)){
		*head = tda_base_node(data);
		index = 1;
	} else {
		tmp = *head;
		while(tmp->tda_next) tmp = tmp->tda_next;
		tmp->tda_next = tda_base_node(data);
		tmp->tda_next->tda_last = tmp;
		tda_set_indexes(head);
		index = tmp->tda_next->tda_index;
	}
	return index;
}

int tda_base_insf(tda_base_t **head, void *data)
{
	
	if( *head && (*head)->tda_type == TDA_CIRCULAR_LIST) return -1; 
	if(!(*head)){
		
		*head = tda_base_node(data);
	} else {
		
		tda_base_t *tmp = *head;
		tmp->tda_last = tda_base_node(data);
		tmp->tda_last->tda_next = *head;
		*head = tmp->tda_last;
	}
	
	tda_set_indexes(head);
	return (*head)->tda_index;
}

int tda_base_ins(tda_base_t **head, int idx,void *data)
{
	int index=0;
	if(*head && (*head)->tda_type == TDA_STACK) return -1;
	if(!(*head)){
		*head = tda_base_node(data); 
	} else {
		tda_base_t *last = tda_base_search(head,idx);
		tda_base_t *tmp = tda_base_node(data);
		tmp->tda_next = (last)->tda_next;
		tmp ->tda_last = last;
		(last)->tda_next = tmp;
		tda_set_indexes(head);
		index = tmp->tda_index;
	}
	return index;
}

tda_base_t *tda_base_search(tda_base_t **head, int index)
{
	int starting = 1;
	tda_base_t *tmp = *head;
	if(tmp->tda_type != TDA_CIRCULAR_LIST){
		while(tmp && tmp->tda_index != index)
			tmp = tmp->tda_next;
	} else {
		while( ((tmp != *head && starting == 0) || (tmp == *head && starting != 0)) && tmp->tda_index != index){
			tmp = tmp->tda_next;
			starting = 0;
		}
	}
	return tmp;
}

void tda_base_setdata(tda_base_t **head, void *data, int index)
{
	tda_base_t *tmp = tda_base_search(head,index);
	tmp->tda_data = (void *) data;
}

void *tda_base_getdata(tda_base_t **head, int index)
{
	tda_base_t *tmp = tda_base_search(head,index);
	return tmp->tda_data;
}

void tda_base_delete(tda_base_t **head, int index)
{
	tda_base_t *tmp = *head;
	int found = 0;

	while(tmp && !found){
		found = tmp->tda_index == index;
		if(!found) tmp = tmp->tda_next;
	}

	if(tmp){
		if(tmp == *head){
			*head = tmp->tda_next;
			if(tmp->tda_next) tmp->tda_next->tda_last = NULL;
		} else if(tmp->tda_next){
			tmp->tda_last->tda_next = tmp->tda_next;
			tmp->tda_next->tda_last = tmp->tda_last;
		} else tmp->tda_last->tda_next = NULL;
		free(tmp);
	}
}

int tda_get_end(tda_base_t **head)
{
	tda_base_t *tmp = *head;
	if(*head){
		if(tmp->tda_type != TDA_CIRCULAR_LIST) while(tmp->tda_next) tmp=tmp->tda_next;
		else while(tmp->tda_next != *head) tmp=tmp->tda_next;
		return tmp->tda_index;
	}
	return 0;
}

void tda_base_destroy(tda_base_t **head)
{
	tda_base_t *tmp = *head, *last=NULL;
	int i = tda_get_end(head), cont=1;
	tmp = tda_base_search(head,i);

	while(cont){
		cont = (!tmp && tmp->tda_type != TDA_CIRCULAR_LIST) || (tmp->tda_type == TDA_CIRCULAR_LIST && tmp != *head);
		last = tmp->tda_last;
		tda_base_delete(head,tmp->tda_index);
		tmp = last;
	}
	*head = NULL;
}

void tda_base_show(tda_base_t **head)
{
	int starting = 1;
	if(!(*head)) return;
	tda_base_t *tmp = *head;
	if(tmp->tda_type != TDA_CIRCULAR_LIST){
		while(tmp){
			printf("[%2d] { #node#%10p\t#node->next#%10p\t#node->last#%10p }\n",tmp->tda_index,tmp,tmp->tda_next,tmp->tda_last);
			tmp = tmp->tda_next;
		}
	} else {
		tmp = *head;
		for(; (tmp != *head && starting == 0) || (tmp == *head && starting != 0);){
			printf("[%2d] { #node#%10p\t#node->next#%10p\t#node->last#%10p }\n",tmp->tda_index,tmp,tmp->tda_next,tmp->tda_last);
			tmp = tmp->tda_next;
			starting = 0;
		}
	}

	puts("");
}

static void tda_convert_circular(tda_base_t **head)
{
	if( (*head)->tda_type != TDA_CIRCULAR_LIST){
		tda_base_t *tmp = *head;
		tmp->tda_type = TDA_CIRCULAR_LIST;
		for(;tmp->tda_next;) tmp=tmp->tda_next;
		(*head)->tda_last = tmp;
		tmp->tda_next=*head;
	}
}

void tda_set_type(tda_base_t **head, tda_type_t type)
{
	if(!(*head)) return;
	if(type == TDA_CIRCULAR_LIST)
		tda_convert_circular(head);
	else {
		(*head)->tda_type = type;
	}
}


int tda_base_len(tda_base_t **list)
{
	int count = 0;
	tda_base_t *tmp = *list;

	while(tmp){
		tmp = tmp->tda_next;
		count++;
	}
	return count;
}
