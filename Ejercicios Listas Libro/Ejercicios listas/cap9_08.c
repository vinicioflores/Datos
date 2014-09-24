#include "cap9.h"

#define SUBCONJ_START    -10

void c_agregarElemento(tda_base_t **conj, int n)
{
	if(n < 0) n = -n;
	tda_base_savedat(conj,&n,tda_base_add(conj,NULL),sizeof(int) );
}

void c_agregarElementos(tda_base_t **conj, tda_base_t **c2)
{
	int i,maxlen,d,j;
	
	for(i=1,j=0;j<2;j++,i=1){
		printf("Creacion de conjunto %d\n\n", j+1);
		printf(" :Inserte numero maximo de elementos para conjunto %d: ", j+1); scanf("%d", &maxlen);
		while(i <= maxlen){
			fflush(stdin); fflush(stdout);
			printf("Inserte elemento %d: ", i); scanf("%d", &d);
			if(!j) c_agregarElemento(conj,d);
			else c_agregarElemento(c2,d);
			i++;
		}
	} 
}

void c_printConjunto(tda_base_t **conj)
{
	bool cond=(*conj && (*conj)->tda_next),starting=true;
	tda_base_p ptr=tda_get_head(conj);
	tda_base_p pHead=*conj;
	printf("C = { ");

	for(;cond && ptr;){
			cond = (  (  (pHead->tda_type >= TDA_CIRCULAR_LIST) && (ptr != tda_get_head(conj) && !starting) ) || (   (pHead->tda_type < TDA_CIRCULAR_LIST) && ptr)  );
			if(tda_iget(conj,ptr->tda_index)  == SUBCONJ_START) printf("{");
			else if(tda_iget(conj,ptr->tda_index) == SUBCONJ_START+1 ) printf("}");
			else printf(" %d%c", tda_iget(conj,ptr->tda_index), (ptr->tda_next) ? ',' : ' ' );
			ptr = ptr->tda_next; 
			starting = false;
	}
	puts("} \n");
}


void printConjuntos(tda_base_t **C1,tda_base_t**C2)
{
	c_printConjunto(C1);
	c_printConjunto(C2);
}

int c_cardinal(tda_base_t **conj)
{
	return tda_base_len(conj); 
}

bool c_pertenece(tda_base_t **conj, int elem)
{
	bool cond = (*conj && (*conj)->tda_next);
	tda_base_p tmp=tda_get_head(conj);
	for(;cond && tmp;){
		cond = ( (((*conj)->tda_type >= TDA_CIRCULAR_LIST) && (tmp != tda_get_head(conj))) || ( ((*conj)->tda_type < TDA_CIRCULAR_LIST) && tmp));
		if( *((int *) tmp->tda_data ) == elem ) return true;
		tmp = tmp->tda_next;
	}
	return false;
}

tda_base_t *unionc(tda_base_t **conj1, tda_base_t **conj2, tda_type_t list_type)
{
	bool cond = (*conj1 && (*conj1)->tda_next);
	tda_base_p p1=tda_get_head(conj1);
	tda_base_p p2=tda_get_head(conj2);
	tda_base_t *retlist=NULL;

	tda_set_type(&retlist,list_type);

	for(;cond && p1;){
		cond = (  (list_type >= TDA_CIRCULAR_LIST) && (p1 != tda_get_head(conj1)) ) || (  (list_type < TDA_CIRCULAR_LIST) && p1 );
		c_agregarElemento(&retlist,*((int *)p1->tda_data));
		p1 = p1->tda_next;
	}

	cond = (*conj2 && (*conj2)->tda_next);

	for(;cond && p2;){
		cond = ( (list_type >= TDA_CIRCULAR_LIST) && (p2 != tda_get_head(conj2)) ) || ( (list_type < TDA_CIRCULAR_LIST) && p2 );
		if(!c_pertenece(conj1,*((int*)p2->tda_data))) c_agregarElemento(&retlist,*((int*)p2->tda_data));
		p2 = p2->tda_next;
	}
	return retlist;
}

tda_base_t *interseccionc(tda_base_t **conj1, tda_base_t **conj2, tda_type_t list_type)
{
	bool cond = (*conj1 && (*conj1)->tda_next);
	tda_base_p p1=tda_get_head(conj1);
	tda_base_t *retlist=NULL;

	tda_set_type(&retlist,list_type);

	for(;cond && p1;){
		cond = ( (list_type >= TDA_CIRCULAR_LIST) && (p1 != tda_get_head(conj1)) ) || ( (list_type < TDA_CIRCULAR_LIST) && p1 );
		if(c_pertenece(conj2, *((int*)p1->tda_data))) c_agregarElemento(&retlist, *((int*)p1->tda_data));
		p1 = p1->tda_next;
	}
	return retlist;
}

tda_base_t *diferenciac(tda_base_t **conj1, tda_base_t **conj2, tda_type_t list_type)
{
	bool cond = (*conj1 && (*conj1)->tda_next);
	tda_base_p p1=tda_get_head(conj1);
	tda_base_t *retlist=NULL;

	tda_set_type(&retlist,list_type);

	for(;cond && p1;){
		cond = ( (list_type >= TDA_CIRCULAR_LIST) && (p1 != tda_get_head(conj1)) ) || ( (list_type < TDA_CIRCULAR_LIST) && p1 );
		if(!c_pertenece(conj2, *((int*)p1->tda_data))) c_agregarElemento(&retlist, *((int*)p1->tda_data));
		p1 = p1->tda_next;
	}
	return retlist;
}

tda_base_t *inclusionc(tda_base_t **conj1, tda_base_t **conj2, tda_type_t list_type)
{
	tda_base_t *retlist=NULL;

	int mark1 = SUBCONJ_START;
	int mark2 = SUBCONJ_START+1;
	tda_set_type(&retlist,list_type);
	tda_base_add_all(&retlist,conj1);
	tda_base_add(&retlist,&mark1);
	tda_base_add_all(&retlist, conj2);
	tda_base_add(&retlist,&mark2);

	return retlist;
}

static void ask_agregar(tda_base_t **conj, tda_base_t **c2)
{
	int num,ncon;
	printf("   - Inserte el numero de conjunto al que desea agregar (0/1): "); scanf("%d",&ncon);
	printf("Inserte entero: "); scanf("%d",&num);

	switch(ncon){
		case 0:
			c_agregarElemento(conj,num);	
			break;
		case 1:
			c_agregarElemento(c2,num);
			break;
		}
}

void c_verificarPertenencia(tda_base_t **conj, tda_base_t **c2, tda_type_t listype)
{
	char add=0;
	int op=1,num,ncon, card;
	do {
		clear();
		printConjuntos(conj,c2);
		printf("\nInserte [0:Salir, 1:Verificar, 2:Unir, 3: Agregar, 4: Interseccion, 5: Diferencia, 6: Inclusion, 7: Cardinalidad] = "); scanf("%d",&op);
		if(op==1){
			printf("Inserte numero de conjunto (0/1): "); scanf("%d",&ncon);
			printf("\nInserte numero entero positivo: "); scanf("%d",&num);
			printf("\t-> %d pertenece a C: %s\n",num, ( (!ncon) ? c_pertenece(conj,num) : c_pertenece(c2,num)  ) ? "Verdadero" : "Falso"); 
			fflush(stdin); fflush(stdout);
			printf(" Desea agregar un nuevo entero a algun conjunto (y/N)? "); scanf("%c",&add);
			if(add=='y' || add=='Y') ask_agregar(conj,c2);
		} else if(op==2) *conj = unionc(conj,c2,listype);
		else if(op==3) ask_agregar(conj,c2);
		else if(op==4) *conj = interseccionc(conj,c2,listype);
		else if(op==5) *conj = diferenciac(conj,c2,listype);
		else if(op==6){
				printf("Inserte numero de conjunto destino (0/1): "); scanf("%d", &ncon);
				switch(ncon){
				case 0:
				*conj = inclusionc(conj,c2,listype);
				break;		
				case 1:
				*c2 = inclusionc(c2,conj,listype);
				break;
			}	 
		} else if(op==7){
			printf("Inserte el numero de conjunto al que desea calcular la Cardinalidad (0/1): "); scanf("%d", &ncon);
			switch(ncon){
				case 0:
				card = c_cardinal(conj);
				break;
				case 1:
				card = c_cardinal(c2);
				break;
			}
			printf("Cardinalidad de C[%d] = %d\n", ncon+1, card);
			pause();
		}
	} while(op);
}

void les_problema8()
{
	system("color 9");
	tda_simple_list_t *conjunto=NULL, *c2=NULL;
	tda_set_type(&conjunto, TDA_SIMPLE_LIST);
	tda_set_type(&c2, TDA_SIMPLE_LIST);
	c_agregarElementos(&conjunto,&c2);
	puts("Conjunto 1");
	tda_tshow(&conjunto,INT); puts("Conjunto2");
	tda_tshow(&c2,INT); pause();
	printConjuntos(&conjunto,&c2);
	printf("\nCardinalidad del conjunto 1: %d\n", c_cardinal(&conjunto) );
	printf("\nCardinalidad del conjunto 2: %d\n", c_cardinal(&c2) );
	c_verificarPertenencia(&conjunto,&c2,TDA_SIMPLE_LIST);
}


void led_problema8()
{
	system("color 9");
	tda_double_list_t *conjunto=NULL, *c2=NULL;
	tda_set_type(&conjunto, TDA_DOUBLE_LIST);
	tda_set_type(&c2, TDA_DOUBLE_LIST);
	c_agregarElementos(&conjunto,&c2);
	printConjuntos(&conjunto,&c2);
	tda_tshow(&conjunto,INT); 
	tda_tshow(&c2, INT); 
	printf("\nCardinalidad del conjunto 1: %d\n", c_cardinal(&conjunto) );
	printf("\nCardinalidad del conjunto 2: %d\n", c_cardinal(&c2) ); pause();
	c_verificarPertenencia(&conjunto,&c2,TDA_DOUBLE_LIST);
}

void lec_problema8()
{
	system("color 9");
	tda_simple_circle_list_t *conjunto=NULL, *c2=NULL;
	tda_set_type(&conjunto, TDA_CIRCULAR_LIST);
	tda_set_type(&c2, TDA_CIRCULAR_LIST);
	c_agregarElementos(&conjunto,&c2);
	printConjuntos(&conjunto,&c2);
	tda_tshow(&conjunto,INT); 
	tda_tshow(&c2, INT); 
	printf("\nCardinalidad del conjunto 1: %d\n", c_cardinal(&conjunto) );
	printf("\nCardinalidad del conjunto 2: %d\n", c_cardinal(&c2) );
	pause();
	c_verificarPertenencia(&conjunto,&c2,TDA_CIRCULAR_LIST);
}


void ledc_problema8()
{
	system("color 9");
	tda_double_circle_list_t *conjunto=NULL, *c2=NULL;
	tda_set_type(&conjunto, TDA_DOUBLE_CIRCULAR_LIST);
	tda_set_type(&c2, TDA_DOUBLE_CIRCULAR_LIST);
	c_agregarElementos(&conjunto,&c2);
	printConjuntos(&conjunto,&c2);
	tda_tshow(&conjunto,INT); pause();
	tda_tshow(&c2, INT); pause();
	printf("\nCardinalidad del conjunto 1: %d\n", c_cardinal(&conjunto) );
	printf("\nCardinalidad del conjunto 2: %d\n", c_cardinal(&c2) );
	c_verificarPertenencia(&conjunto,&c2,TDA_DOUBLE_CIRCULAR_LIST);
}

