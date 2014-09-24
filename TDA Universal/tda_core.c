#include "tda_core.h"

<<<<<<< HEAD
bool tda_base_isempty(tda_base_t **head){ return (bool)( tda_get_head(head) == NULL) ; }
=======
static tda_base_t *tda_base_node(void *pData);
static tda_base_t *tda_base_node_copy(void *data);
>>>>>>> origin/master

void tda_set_indexes(tda_base_t **head)
{
	tda_base_t *tmp = *head;
	int i = 0;

<<<<<<< HEAD
	if((*head)->tda_type != TDA_CIRCULAR_LIST){
		while(tmp){
			tmp->tda_index = i;
			tmp = tmp->tda_next;
			i++;
		}
	} else {
		while(tmp->tda_next != tda_get_head(head)); {
			tmp->tda_index = i;
			tmp = tmp->tda_next;
			i++;
		} 
=======
	while(tmp){
		tmp->tda_index = i;
		tmp = tmp->tda_next;
		i++;
>>>>>>> origin/master
	}
}

void tda_base_nnew(tda_base_t **head, int maxn)
{
	for(;maxn;maxn--)
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
	memcpy(node->tda_data, data, sizeof(data));	
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
<<<<<<< HEAD
	return tda_base_ins(head,0,data);
=======
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
>>>>>>> origin/master
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
		tda_set_indexes(head);
		return 1;
	} else {
		new->tda_type = (*head)->tda_type;
		while(after && !found){
			if(after->tda_index != index) after=after->tda_next;
			else found = true;
		}

		if(found){
			if( (after && *head) && ( (*head)->tda_type == TDA_SIMPLE_LIST)  ){
				new->tda_next = after->tda_next;
				new->tda_index = (after->tda_index)+1;
				after->tda_next = new; 
			} else if ( (after && *head) && ( (*head)->tda_type == TDA_DOUBLE_LIST || (*head)->tda_type == TDA_DOUBLE_CIRCULAR_LIST )) {
				new->tda_next = after->tda_next;
				new->tda_last = after;
				new->tda_index = (new->tda_last->tda_index)+1;
				after->tda_next = new;
			} else if( (after && *head) &&  ( (*head)->tda_type == TDA_CIRCULAR_LIST  )  ){

				tda_base_t *hd=tda_get_head(head);
				if(!tda_base_isempty (head) ){
					new->tda_next = hd->tda_next;
					hd->tda_next = new;
				}

				hd = new;
			}
			tda_set_indexes(head);
			return new->tda_index;
		}
	}
	return TDA_ERR_INVALID_INSERTION;
}

tda_base_t *tda_base_search(tda_base_t **head, int index)
{
	int starting = 1;
<<<<<<< HEAD
	tda_base_t *tmp = (*head);
	if(tmp){
		if(tmp->tda_type != TDA_CIRCULAR_LIST){
			while(tmp && tmp->tda_index  != index)
				tmp = tmp->tda_next;
		} else {
			if(tda_get_head(head)){
				while( ((tmp != tda_get_head(head) && starting == 0) || (tmp == tda_get_head(head) && starting != 0)) && tmp->tda_index != index){
					tmp = tmp->tda_next;
					starting = 0;
				}
			}
=======
	tda_base_t *tmp = *head;
	if(tmp->tda_type != TDA_CIRCULAR_LIST){
		while(tmp->tda_index != index)
			tmp = tmp->tda_next;
	} else {
		while( ((tmp != *head && starting == 0) || (tmp == *head && starting != 0)) && tmp->tda_index != index){
			tmp = tmp->tda_next;
			starting = 0;
>>>>>>> origin/master
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
<<<<<<< HEAD
	if(tmp) return tmp->tda_data;
	return NULL;
=======
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
>>>>>>> origin/master
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
		printf("Liberar %p ... \n", tmp);
		if(tmp) free(tmp);
		printf("Indexar desde cabeza %p\n",*head);
		if(*head) tda_set_indexes(head);
}

int tda_get_end(tda_base_t **head)
{
	tda_base_t *tmp = *head;
	if(*head){
		if(tmp->tda_type != TDA_CIRCULAR_LIST) while(tmp->tda_next) tmp=tmp->tda_next;
		else  while(tmp && tmp->tda_next && tmp->tda_next != tda_get_head(head)) tmp=tmp->tda_next; 
		if(tmp) return tmp->tda_index;
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
	if(tmp->tda_type != TDA_CIRCULAR_LIST){
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


void tda_convert_simple(tda_base_t **head){
	tda_base_t *p = *head;
		p->tda_type = TDA_SIMPLE_LIST;
		while(p){
			p->tda_last = NULL;
			p = p->tda_next;
		}
}

void tda_convert_double(tda_base_t **head){
	if(!(*head))
		*head = tda_base_node(NULL);
	(*head)->tda_type = TDA_DOUBLE_LIST;
}

void tda_print_type(tda_base_t **head)
{
	char st[35];
	if((*head)->tda_type == TDA_SIMPLE_LIST) sprintf(st,"SimpleList\n");
	else if((*head)->tda_type == TDA_DOUBLE_LIST) sprintf(st,"DoubleList\n");
	else if((*head)->tda_type == TDA_CIRCULAR_LIST) sprintf(st,"CircleList\n");
	else if((*head)->tda_type == TDA_DOUBLE_CIRCULAR_LIST) sprintf(st, "DoubleCircleList\n");
	else if((*head)->tda_type == TDA_STACK) sprintf(st, "Stack\n");
	printf("%s",st);
}

void tda_base_savedat(tda_base_t **head, void *data, int index, size_t size)
{
	tda_base_t *p = tda_base_search(head,index);
	if(p){ p->tda_data = malloc(size);
		   memcpy(p->tda_data,(const void*)data,size);
		}
}

void tda_set_type(tda_base_t **head, tda_type_t type)
{
	if(!(*head)){ *head=tda_base_node(NULL); (*head)->tda_type = type; }
	if(type == TDA_CIRCULAR_LIST) tda_convert_circular(head);
	else if(type == TDA_SIMPLE_LIST) tda_convert_simple(head);
	else if(type == TDA_DOUBLE_LIST) tda_convert_double(head);
	else (*head)->tda_type = type;
}


int tda_base_len(tda_base_t **list)
{
	int count = 0;
	tda_base_t *tmp = (*list)->tda_next;

	while(tmp){
		tmp = tmp->tda_next;
		count++;
	}
	return count;
}


tda_base_t *tda_get_head(tda_base_t **head) {
	if(*head){
		tda_base_p pt=*head;
		if(pt->tda_type == TDA_CIRCULAR_LIST || pt->tda_type == TDA_DOUBLE_CIRCULAR_LIST) return (*head)->tda_next;
		else {
			return *head;
		}
	}


	else return *head;
	return NULL;
}

