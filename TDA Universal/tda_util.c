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
	return *((char *) tda_base_getdata(head,index));
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
	tda_base_t *p = (*head)->tda_next;
 	while(p) {
		switch(type){
			case CHAR:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%c)\n",p,p->tda_index,p->tda_next,p->tda_last,tda_cget(&p,p->tda_index));
				break;
			case INT:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%d)\n",p,p->tda_index,p->tda_next,p->tda_last,tda_iget(&p,p->tda_index));
				break;
			case DOUBLE:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%lf)\n",p,p->tda_index,p->tda_next,p->tda_last,*((double *) tda_base_getdata(&p,p->tda_index)));
				break;
			case FLOAT:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%f)\n",p,p->tda_index,p->tda_next,p->tda_last,*((float *) tda_base_getdata(&p,p->tda_index)));
				break;
			case IEEE:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%e)\n",p,p->tda_index,p->tda_next,p->tda_last,*((float *) tda_base_getdata(&p,p->tda_index)));
				break;
			case POINTER:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%p)\n",p,p->tda_index,p->tda_next,p->tda_last,p->tda_data);
				break;
			case STRING:
				printf("#node:%p#[%4d] #node->next:%p# #node->last:%p# data=(%s)\n",p,p->tda_index,p->tda_next,p->tda_last,tda_sget(&p,p->tda_index));
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
