#include "cap9.h"

void agregarElemento(tda_base_t **conj, int n)
{
	tda_base_savedat(conj,&n,tda_base_add(conj,NULL),sizeof(int));
}

void agregarElementos(tda_base_t **conj)
{
	int i = 1,maxlen,d;
	printf("Inserte numero maximo de elementos: "); scanf("%d", &maxlen);
	while(i <= maxlen){
		printf("Inserte elemento %d: ", i); scanf("%d", &d);
		agregarElemento(conj,d);
		i++;
	}
	clear();
}

void printConjunto(tda_base_t **conj)
{
	bool ciclec=true;
	tda_base_p ptr=tda_get_head(conj);
	printf("C = { ");
	for(;ptr && ciclec;){
		if( (*conj)->tda_type == TDA_CIRCULAR_LIST || (*conj)->tda_type == TDA_DOUBLE_CIRCULAR_LIST )
			ciclec = (ptr != *conj);
		printf(" %d%c", *((int *)ptr->tda_data), (ptr->tda_next) ? ',' : ' ' );
		ptr = ptr->tda_next; 
	}
	puts("} \n");
}

int cardinal(tda_base_t **conj)
{
	return tda_base_len(conj); 
}

bool pertenece(tda_base_t **conj, int elem)
{
	tda_base_p tmp=tda_get_head(conj);
	for(;tmp;){
		if( *((int *) tmp->tda_data ) == elem ) return true;
		tmp = tmp->tda_next;
	}
	return false;
}



void verificarPertenencia(tda_base_t **conj)
{
	char add=0;
	int op=1,num;
	do {
		clear();
		printConjunto(conj);
		printf("\nInserte [0:Salir, 1:Verificar] = "); scanf("%d",&op);
		if(op){
			printf("\nInserte numero entero positivo: "); scanf("%d",&num);
			printf("\t-> %d pertenece a C: %s\n",num, (pertenece(conj,num)) ? "Verdadero" : "Falso"); 
			fflush(stdin); fflush(stdout);
			printf(" Desea agregar un nuevo entero al conjunto (y/N)? "); scanf("%c",&add);

			if(add=='y' || add=='Y'){
				printf("Inserte entero: "); scanf("%d",&num);
				agregarElemento(conj,num);
			}
		}

	} while(op);
}

void les_problema7()
{
	system("color 6");
	tda_simple_list_t *conjunto=NULL;
	tda_set_type(&conjunto, TDA_SIMPLE_LIST);
	agregarElementos(&conjunto);
	printConjunto(&conjunto);
	tda_tshow(&conjunto,INT); pause();
	printf("\nCardinalidad del conjunto: %d\n", cardinal(&conjunto) );
	verificarPertenencia(&conjunto);
}

void led_problema7()
{
	system("color 8");
	tda_double_list_t *conjunto=NULL;
	tda_set_type(&conjunto, TDA_DOUBLE_LIST);
	agregarElementos(&conjunto);
	printConjunto(&conjunto);
	tda_tshow(&conjunto,INT); pause();
	printf("\nCardinalidad del conjunto: %d\n", cardinal(&conjunto) );
	verificarPertenencia(&conjunto);
}

void lec_problema7()
{
	system("color 8");
	tda_simple_circle_list_t *conjunto=NULL;
	tda_set_type(&conjunto, TDA_CIRCULAR_LIST);
	agregarElementos(&conjunto);
	printConjunto(&conjunto);
	tda_tshow(&conjunto,INT); pause();
	printf("\nCardinalidad del conjunto: %d\n", cardinal(&conjunto) );
	verificarPertenencia(&conjunto);
}

void ledc_problema7()
{
	system("color 8");
	tda_double_circle_list_t *conjunto=NULL;
	tda_set_type(&conjunto, TDA_DOUBLE_CIRCULAR_LIST);
	agregarElementos(&conjunto);
	printConjunto(&conjunto);
	tda_tshow(&conjunto,INT); pause();
	printf("\nCardinalidad del conjunto: %d\n", cardinal(&conjunto) );
	verificarPertenencia(&conjunto);
}

