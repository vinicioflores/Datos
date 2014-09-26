#include "tda_core.h"

bool tda_base_isempty(tda_base_t **head){ return (bool)( tda_get_head(head) == NULL) ; }
void tda_set_indexes(tda_base_t **head)
{
	if(!(*head)) return;

	int i = 0;
	tda_base_t *tmp = *head;

	if( tmp->tda_type != TDA_CIRCULAR_LIST && tmp->tda_type != TDA_DOUBLE_CIRCULAR_LIST ){
		while(tmp){
			tmp->tda_index = i;
			tmp = tmp->tda_next;
			i++;
		}
	} else {
		while(tmp && tmp != *head){
			tmp->tda_index = i;
			tmp = tmp->tda_next;
			i++;
		}
	}
}

void tda_base_nnew(tda_base_t **head, int maxn)
{
	for(;maxn;maxn--)
		tda_base_add(head,NULL);
}

tda_base_t *tda_base_node(void *data)
{
	tda_base_t *node = (tda_base_t *) malloc (sizeof(tda_base_t));
	node->tda_data = data;
	node->tda_next = NULL;
	node->tda_last = NULL;
	node->tda_index = 0;
	return node;
}

void tda_base_add_all(tda_base_t **head, tda_base_t **src)
{
	tda_base_p p2 = tda_get_head(src);

	for(;p2;){
		tda_base_add(head, p2->tda_data);
		p2 = p2->tda_next;
	}
}

int tda_base_add(tda_base_t **head, void *data)
{
	return tda_base_ins(head,tda_get_end(head),data);
}

int tda_base_insf(tda_base_t **head, void *data)
{
	return tda_base_ins(head,0,data);
}

int tda_base_ins(tda_base_t **head,int index,void *data)
{
	/* Si vamos a insertar un elemento en una pila
		debemos validar que sólo sea válido
		colocarlo al tope de la pila,
		si la posición es inválida devolvemos 
		un codigo de error */
	if(*head && (*head)->tda_type == TDA_STACK){
		if(index != tda_get_end(head) && index != TDA_INIT_INDEX)
			return TDA_ERR_INVALID_INSERTION;
	}
	bool found=false;
	tda_base_t *new=tda_base_node(data),*after=*head;

	if(!(*head)) return TDA_ERR_INVALID_INSERTION;
	else if(!(*head)->tda_next && index == 0){
		(*head)->tda_next=tda_base_node(data);
		(*head)->tda_next->tda_type = (*head)->tda_type;
		if( (*head)->tda_type == TDA_CIRCULAR_LIST || (*head)->tda_type == TDA_DOUBLE_CIRCULAR_LIST ){
			(*head)->tda_next->tda_next = *head;
		}
		tda_set_indexes(head);
		return 1;
	} else {
		new->tda_type = (*head)->tda_type;
		while(after && !found){
			if(after->tda_index != index) after=after->tda_next;
			else found = true;
		}

		if(found){
			if(after && *head){
				if( ( (*head)->tda_type == TDA_SIMPLE_LIST) || ( (*head)->tda_type == TDA_CIRCULAR_LIST) ){
					new->tda_next = after->tda_next;
					new->tda_index = (after->tda_index)+1;
					after->tda_next = new; 

				} else if ( ( (*head)->tda_type == TDA_DOUBLE_LIST || (*head)->tda_type == TDA_DOUBLE_CIRCULAR_LIST )) {
					new->tda_next = after->tda_next;
					new->tda_last = after;
					new->tda_index = (new->tda_last->tda_index)+1;
					after->tda_next = new;
				}
			}

			tda_set_indexes(head);
			return new->tda_index;
		}
	}
	return TDA_ERR_INVALID_INSERTION;
}

tda_base_t *tda_base_search(tda_base_t **head, int index)
{
	tda_base_t *tmp =*head;

	if(tmp->tda_type == TDA_CIRCULAR_LIST || tmp->tda_type == TDA_DOUBLE_CIRCULAR_LIST){
		while(tmp != *head){
			if(tmp->tda_index == index) return tmp;
			tmp = tmp->tda_next;
		}
	} else {
		while(tmp){
			if(tmp->tda_index == index) return tmp;
			tmp = tmp->tda_next;
		}
	}
	return NULL;
}

void tda_base_setdata(tda_base_t **head, void *data, int index)
{
	tda_base_t *tmp = tda_base_search(head,index);
	tmp->tda_data = (void *) data;
}

void *tda_base_getdata(tda_base_t **head, int index)
{
	tda_base_t *tmp = tda_base_search(head,index);
	if(tmp) return tmp->tda_data;
	return NULL;
}

void tda_base_delete(tda_base_t **head, int index)
{
	if(!(*head))return;
	tda_type_t saved_type = 0;
	tda_base_t *tmp = *head, *last=NULL;
	int found = 0;
	while(tmp && !found){
		found = (tmp->tda_index == index);
		if(!found){
			last = tmp;
			tmp = tmp->tda_next;
		}
	}
		/* Proceso para eliminar en el caso de que sea una lista enlazada simple */
		if(*head && (*head)->tda_type == TDA_SIMPLE_LIST){
			if(tmp==*head) *head = tmp->tda_next;
			else { if(last && tmp) last->tda_next = tmp->tda_next; }
		} else if((*head)->tda_type == TDA_DOUBLE_LIST){
			if(tmp == *head){
				saved_type = (*head)->tda_type;
				*head = tmp->tda_next;
				(*head)->tda_type = saved_type;
				if(tmp->tda_next) tmp->tda_next->tda_last = NULL;
			} else if(tmp && tmp->tda_next && tmp->tda_last){
				tmp->tda_last->tda_next = tmp->tda_next; 
				tmp->tda_next->tda_last = tmp->tda_last;
			} else if(tmp->tda_last && tmp) tmp->tda_last->tda_next = NULL;
		}
		
		if(tmp) free(tmp);
		if(*head) tda_set_indexes(head);
}

int tda_get_end(tda_base_t **head)
{
	tda_base_t *tmp = *head;
	if(*head){
		if(tmp->tda_type != TDA_CIRCULAR_LIST && tmp->tda_type != TDA_DOUBLE_CIRCULAR_LIST) while(tmp->tda_next) tmp=tmp->tda_next;
		else  while(tmp && tmp->tda_next && (tmp->tda_next != tda_get_head(head)) ) tmp=tmp->tda_next; 
		return tmp->tda_index;
	}
	return 0;
}

void tda_base_destroy(tda_base_t **head)
{
	tda_base_t *tmp = *head;
	int i = tda_get_end(head);
	tmp = tda_base_search(head,i);

	while(i>0) tda_base_delete(head,i--);
}

void tda_base_show(tda_base_t **head)
{
	int starting = 1;
	if(!(*head)) return;
	tda_base_t *tmp = (*head)->tda_next;
	if(tmp && tmp->tda_type != TDA_CIRCULAR_LIST){
		while(tmp){
			printf("[%2d] (0x%x) {\n #node#%10p\t#node->next#%10p\t#node->last#%10p \n\t\t}\n",tmp->tda_index,(int)tmp->tda_data,tmp,tmp->tda_next,(tmp==(*head)->tda_next) ? NULL : tmp->tda_last);
			tmp = tmp->tda_next;
			printf("\n");
		}
	} else {
		for(; (tmp != *head && starting == 0) || (tmp == *head && starting != 0);){
			printf("[%2d] (0x%x) { \n #node#%10p\t#node->next#%10p\t#node->last#%10p \n\t\t}\n",tmp->tda_index,(int)tmp->tda_data,tmp,tmp->tda_next,(tmp==(*head)->tda_next) ? NULL : tmp->tda_last);
			tmp = tmp->tda_next;
			starting = 0;
			printf("\n");
		}
	}

	puts("");
}

void tda_convert_circular(tda_base_t **head)
{
	if(!(*head)){ *head = tda_base_node(NULL);  (*head)->tda_type = TDA_CIRCULAR_LIST; return; }
	tda_base_p tmp=*head;
	tmp->tda_type = TDA_CIRCULAR_LIST;
	for(;tmp->tda_next;){
		tmp->tda_last = NULL;
		tmp = tmp->tda_next;
	}
	if(!tmp->tda_next) tmp->tda_next = *head;
}

void tda_convert_double_circular(tda_base_t **head)
{
		if(!(*head)){ *head = tda_base_node(NULL);  (*head)->tda_type = TDA_DOUBLE_CIRCULAR_LIST; return; }
		if( (*head)->tda_type != TDA_DOUBLE_LIST && (*head)->tda_type != TDA_DOUBLE_CIRCULAR_LIST ) tda_convert_double(head);
		tda_base_t *tmp = *head, *last=*head;
		tmp->tda_type = TDA_DOUBLE_CIRCULAR_LIST;

		for(;tmp->tda_next;){
			tmp->tda_last = last;
			last = tmp;
			tmp=tmp->tda_next;
		}
		
		(*head)->tda_next->tda_last = tmp;
		tmp->tda_next=tda_get_head(head);
		tmp->tda_next->tda_last = tmp;
		(*head)->tda_type = TDA_DOUBLE_CIRCULAR_LIST;
}


void tda_convert_simple(tda_base_t **head){
		if(!(*head)){ *head = tda_base_node(NULL);  (*head)->tda_type = TDA_SIMPLE_LIST; return; }
		tda_base_t *p = *head;
		p->tda_type = TDA_SIMPLE_LIST;
		while(p){
			p->tda_last = NULL;
			p = p->tda_next;
		}
}

void tda_convert_double(tda_base_t **head){
	if(!(*head)){ *head = tda_base_node(NULL);  (*head)->tda_type = TDA_DOUBLE_LIST; return; }

	tda_base_p ptmp = *head, last=NULL;
	if(ptmp){
		ptmp->tda_last = last;
		last = ptmp;
		ptmp = ptmp->tda_next;
		for(;ptmp;){
			ptmp->tda_last = last;
			last = ptmp;
			ptmp = ptmp->tda_next;
		}
	}
}

void tda_set_type(tda_base_t **head, tda_type_t type)
{	
	if(type == TDA_CIRCULAR_LIST) tda_convert_circular(head);
	else if(type == TDA_SIMPLE_LIST) tda_convert_simple(head);
	else if(type == TDA_DOUBLE_LIST) tda_convert_double(head);
	else if(type == TDA_DOUBLE_CIRCULAR_LIST) tda_convert_double_circular(head);
}


void tda_print_type(tda_base_t **head)
{
	char st[35];
	if((*head)->tda_type == TDA_SIMPLE_LIST) sprintf(st,"SimpleList");
	else if((*head)->tda_type == TDA_DOUBLE_LIST) sprintf(st,"DoubleList");
	else if((*head)->tda_type == TDA_CIRCULAR_LIST) sprintf(st,"CircleList");
	else if((*head)->tda_type == TDA_DOUBLE_CIRCULAR_LIST) sprintf(st, "DoubleCircleList");
	else if((*head)->tda_type == TDA_STACK) sprintf(st, "Stack");
	printf("%s",st);
}

void tda_base_savedat(tda_base_t **head, void *data, int index, size_t size)
{
	tda_base_t *p = tda_base_search(head,index);
	if(p){ p->tda_data = malloc(size);
		   memcpy(p->tda_data,(const void*)data,size);
		}
}

int tda_base_len(tda_base_t **list)
{
	int count = 0;
	bool cond=true;
	tda_base_t *tmp = (*list)->tda_next;

	while(cond && tmp){
		if( (*list)->tda_type == TDA_CIRCULAR_LIST || (*list)->tda_type == TDA_DOUBLE_CIRCULAR_LIST ) cond = (tmp != tda_get_head(list));
		tmp = tmp->tda_next;
		count++;
	} 
	return count;
}

void tda_base_fill(tda_base_t **list, void *d)
{
	bool cond=true;
	tda_base_p np = *list;

	while(cond && np){
		if( (*list)->tda_type == TDA_CIRCULAR_LIST || (*list)->tda_type == TDA_DOUBLE_CIRCULAR_LIST ){
			cond = (np != tda_get_head(list) );
		}
		if(np->tda_data) free(np->tda_data);
		tda_base_savedat(list,d,np->tda_index,sizeof(d));
		np = np->tda_next;
	}
}


tda_base_t *tda_get_head(tda_base_t **head) {
	if(*head) return (*head)->tda_next;
	return NULL;
}

