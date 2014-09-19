#include "tda_core.h"

static tda_base_t *tda_base_node(void *pData);
static tda_base_t *tda_base_node_copy(void *data);

void tda_set_indexes(tda_base_t **head)
{
	tda_base_t *tmp = *head;
	int i = 1;

	while(tmp){
		tmp->tda_index = i;
		tmp = tmp->tda_next;
		i++;
	}
}

void tda_base_nnew(tda_base_t **head, int maxn)
{
	int i;

	for(i=0;i<maxn;i++)
		tda_base_add(head,NULL);

}

/*retorna un nodo de la lista donde dato es guardado
por referencia al data original */
static tda_base_t *tda_base_node(void *data)
{
	tda_base_t *node = (tda_base_t *) malloc (sizeof(tda_base_t));
	//obetner memoria para hacer una copia del dato generico
	node-> dataCopied = 0;
	node-> tda_data = data;
	node->tda_next = NULL;
	node->tda_last = NULL;
	node->tda_index = TDA_INIT_INDEX;
	tda_set_indexes(&node);
	return node;
}

/*retorna un nodo de la lista donde el dato es copiado
al heap y un puntero a tal es guardado en dato */
static tda_base_t *tda_base_node_copy(void *data)
{
	tda_base_t *node = (tda_base_t *) malloc (sizeof(tda_base_t));
	//obetner memoria para hacer una copia del dato generico
	node-> dataCopied = 1;
	node-> tda_data = malloc(sizeof(data));
	memcpy(node->tda_data, data, sizeof(&data));	
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

//agrega un elemento copiando ese elento a memoria
int tda_base_add_copy (tda_base_t **head, void *data){
	tda_base_t *tmp=NULL;
	int index = 0;
	if(!(*head)){
		*head = tda_base_node_copy(data);
		index = 1;
	} else {
		tmp = *head;
		while(tmp->tda_next) tmp = tmp->tda_next;
		tmp->tda_next = tda_base_node_copy(data);
		tmp->tda_next->tda_last = tmp;
		tda_set_indexes(head);
		index = tmp->tda_next->tda_index;
	}
	return index;

}

int tda_base_insf(tda_base_t **head, void *data)
{
	if( (*head)->tda_type != TDA_BASE || (*head)->tda_type != TDA_SIMPLE_LIST) return -1;
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
		while(tmp->tda_index != index)
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

static void tda_base_del(tda_base_t **head,tda_base_t **dnode){
	//printf("call tda_base_del ... \n");
	tda_base_t *tmp = *dnode;
	if(!(*head) || !(*dnode)) return;
	else if(*head && !((*head)->tda_last) && !((*head)->tda_next))
		*head = NULL;
	else if(!tmp->tda_last && tmp->tda_next){
		(*head) = tmp->tda_next;
		//si dato fue copiado
		if(tmp->dataCopied)
			free(tmp->tda_data);
		free(tmp);

	} else if(tmp->tda_last && !tmp->tda_next){
		tmp->tda_last->tda_next = NULL;
		//si dato fue copiado
		if(tmp->dataCopied)
			free(tmp->tda_data);
		free(tmp);
	} else {
		(tmp)->tda_last->tda_next = (tmp)->tda_next;
		(tmp)->tda_next->tda_last = (tmp->tda_last);
		tmp=NULL;
	}
	if(*head){//printf("Rebuilding indexes ... \n");
	 tda_set_indexes(head);}
	//printf("tda_base_del ret \n");
}

void tda_base_delete(tda_base_t **head, int index)
{
	tda_base_t *tmp = tda_base_search(head,index);
	tda_base_del(head,&tmp);
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
		tda_base_del(head,&tmp);
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

