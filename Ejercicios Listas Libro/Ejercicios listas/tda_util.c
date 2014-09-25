/**
	Implementa funciones de utilidad
	basadas en el TDA universal **/

#include "tda_util.h"

void tda_randgen(tda_base_t **head, int n, int range)
{
	int val=0, itmp = 0;
	for(; n; n--){
		srand(time(NULL)*rand());
		val = rand()%range;
		itmp = tda_base_insf(head,NULL);
		tda_base_savedat(head,(void *)(&val), itmp, sizeof(int));
	}
}

char tda_cget(tda_base_t **head, int index)
{
	void *dat = tda_base_getdata(head,index);
	if(dat) return *( (char *)dat );
	else return (char)TDA_ERR_INVALID_DATA;
}

int tda_iget(tda_base_t **head, int index)
{
	void *dat = tda_base_getdata(head,index);
	if(dat) return *((int *) dat);
	else return TDA_ERR_INVALID_DATA;
}

float tda_fget(tda_base_t **head, int index)
{
	float val = *((float *) tda_base_getdata(head,index));
	return val;
}

double tda_lfget(tda_base_t **head, int index)
{
	double val = *((double *) tda_base_getdata(head,index));
	return val;
}

char* tda_sget(tda_base_t **head, int index)
{
	return ((char *) tda_base_getdata(head,index));
}

void tda_tshow(tda_base_t **head, tda_data_t type)
{
	bool cicle_cond = true, starting = false;
	tda_base_t *p = tda_get_head(head);
	tda_base_p pHead = *head;
	printf("-> Head: %p, next: %p [", *head, pHead->tda_next);
	tda_print_type(head); puts("]");
 	while(p && cicle_cond) {
 		if(pHead->tda_type == TDA_CIRCULAR_LIST || pHead->tda_type == TDA_DOUBLE_CIRCULAR_LIST)
 			cicle_cond = (p->tda_next != *head);
		switch(type){
			case CHAR:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%c)\n",p,p->tda_index,p->tda_next,p->tda_last,tda_cget(&pHead,p->tda_index));
				break;
			case INT:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%d)\n",p,p->tda_index,p->tda_next,p->tda_last,tda_iget(&pHead,p->tda_index));
				break;
			case DOUBLE:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%lf)\n",p,p->tda_index,p->tda_next,p->tda_last,*((double *) tda_base_getdata(&pHead,p->tda_index)));
				break;
			case FLOAT:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%f)\n",p,p->tda_index,p->tda_next,p->tda_last,*((float *) tda_base_getdata(&pHead,p->tda_index)));
				break;
			case SCI:
			case IEEE:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%e)\n",p,p->tda_index,p->tda_next,p->tda_last,*((float *) tda_base_getdata(&pHead,p->tda_index)));
				break;
			case POINTER:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%p)\n",p,p->tda_index,p->tda_next,p->tda_last,p->tda_data);
				break;
			case STRING:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%s)\n",p,p->tda_index,p->tda_next,p->tda_last,tda_sget(&pHead,p->tda_index));
				break;
		}
		p = p->tda_next;
	}
}

void clpause()
{
	pause();
	clear();
}

void pause()
{
	#ifdef _WIN32
		system("Pause");
	#endif
}

void clear()
{
	#ifdef _WIN32
	system("Cls");
	#else
	system("clear");
	#endif
}