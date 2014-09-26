#include "cap9.h"

static void ordenar_burbuja(tda_base_t **head)
{
	tda_base_t *ptmp = tda_get_head(head);
	int inter = 1,j=0, swapIndex=0,i;

	i = tda_base_len(head);
	
	while(i > 0){
		swapIndex = 0;
		for(j=0; ptmp->tda_next && j < i; j++){
			if( *((char *)ptmp->tda_data) >  *((char *)ptmp->tda_next->tda_data) ){
				printf("%c\t%c\n",*((char *)ptmp->tda_data),*((char *)ptmp->tda_next->tda_data));
				void *aux = ptmp->tda_data;
				ptmp->tda_data = ptmp->tda_next->tda_data;
				ptmp->tda_next->tda_data = aux;
			}

			swapIndex = ptmp->tda_index;
			ptmp = ptmp->tda_next;

		} i = swapIndex;
	}
}

void les_problema6()
{
	tda_simple_list_t *charlist=NULL,*p;
	char c = 0;
	int maxn = 0, k = 0,i=0;

	tda_set_type(&charlist,TDA_SIMPLE_LIST);
	printf("Inserte numeros de caracteres a insertar: ");
	scanf("%d",&maxn);

	while(k < maxn) {
		fflush(stdout);fflush(stdin);
		printf("char %d: ", k);
		scanf("%c",&c);
		i = tda_base_add(&charlist,malloc(1));
		p = tda_base_search(&charlist,i);
		memcpy(p->tda_data,(const void *)(&c),1);
		k++;
	}

	ordenar_burbuja(&charlist);
	tda_tshow(&charlist,CHAR);
}

void led_problema6()
{
	tda_double_list_t *charlist=NULL,*p;
	char c = 0;
	int maxn = 0, k = 0,i=0;

	tda_set_type(&charlist,TDA_DOUBLE_LIST);
	printf("Inserte numeros de caracteres a insertar: ");
	scanf("%d",&maxn);

	while(k < maxn) {
		fflush(stdout);fflush(stdin);
		printf("char %d: ", k);
		scanf("%c",&c);
		i = tda_base_add(&charlist,malloc(1));
		p = tda_base_search(&charlist,i);
		memcpy(p->tda_data,(const void *)(&c),1);
		k++;
	}

	ordenar_burbuja(&charlist);
	tda_tshow(&charlist,CHAR);
}

void lec_problema6()
{
	tda_simple_circle_list_t *charlist=NULL,*p;
	char c = 0;
	int maxn = 0, k = 0,i=0;

	tda_set_type(&charlist,TDA_CIRCULAR_LIST);
	printf("Inserte numeros de caracteres a insertar: ");
	scanf("%d",&maxn);

	while(k < maxn) {
		fflush(stdout);fflush(stdin);
		printf("char %d: ", k);
		scanf("%c",&c);
		i = tda_base_add(&charlist,malloc(1));
		p = tda_base_search(&charlist,i);
		memcpy(p->tda_data,(const void *)(&c),1);
		k++;
	}

	ordenar_burbuja(&charlist);
	tda_tshow(&charlist,CHAR);
}

void ledc_problema6()
{
	tda_double_circle_list_t *charlist=NULL,*p;
	char c = 0;
	int maxn = 0, k = 0,i=0;

	tda_set_type(&charlist,TDA_DOUBLE_CIRCULAR_LIST);
	printf("Inserte numeros de caracteres a insertar: ");
	scanf("%d",&maxn);

	while(k < maxn) {
		fflush(stdout);fflush(stdin);
		printf("char %d: ", k);
		scanf("%c",&c);
		i = tda_base_add(&charlist,malloc(1));
		p = tda_base_search(&charlist,i);
		memcpy(p->tda_data,(const void *)(&c),1);
		k++;
	}

	ordenar_burbuja(&charlist);
	tda_tshow(&charlist,CHAR);
}

