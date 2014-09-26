#include "cap9.h"

#define STRING_MAX			512
#define SUBCONJ_START    -1

void readword(char *wordbuf, FILE *pf, bool *nextread)
{
	char c='.';
	int j;

	for(j=0; c!=' ' && c != '\n' && c != '\t' && c!= EOF && c != '\r' && c != ','  && c != '.'; j++){
		c = fgetc(pf);
		wordbuf[j] = c;
		putchar(wordbuf[j]);
	}

	if(c==EOF || feof(pf)) *nextread = false;
}

void s_agregarElemento(tda_base_t **conj, String s, int maxlen)
{
	tda_base_savedat(conj,s,tda_base_add(conj,NULL),maxlen);
}

void s_agregarElementos(tda_base_t **conj, tda_base_t **c2)
{
	int i,j;
	char d[STRING_MAX],fname1[STRING_MAX],fname2[STRING_MAX];
	memset(d,0,STRING_MAX);

	bool nextread = true;
	FILE *f1, *f2;

	printf("Inserte nombre del archivo 1: "); scanf("%s", fname1);
	printf("Inserte nombre del archivo 2: "); scanf("%s", fname2);

	f1 = fopen(fname1, "r");
	f2 = fopen(fname2, "r");

	if(!f1 || !f2) {
		perror("Fallo al abrir uno/ambos archivos. ");
		exit(0);
	}
	
	for(i=1,j=0;j<2;j++,i=1){
		printf("Creacion de conjunto %d\n\n", j+1);
		
		do {
			fflush(stdin); fflush(stdout);
			if(j == 0) readword(d, f1, &nextread);
			else readword(d, f2, &nextread);
			if(!j) s_agregarElemento(conj,d,STRING_MAX);
			else s_agregarElemento(c2,d,STRING_MAX);
			memset(d,0,STRING_MAX);
			i++;
		} while(nextread);
	} 
}

void s_printConjunto(tda_base_t **conj)
{
	bool cond=(*conj && (*conj)->tda_next);
	tda_base_p ptr=tda_get_head(conj);
	tda_base_p pHead=*conj;
	printf("C = { ");
	for(;cond && ptr;){
			cond = (  (  (pHead->tda_type >= TDA_CIRCULAR_LIST) && (ptr != tda_get_head(conj)) ) || (   (pHead->tda_type < TDA_CIRCULAR_LIST) && ptr)  );
			printf(" %s%c", tda_sget(conj,ptr->tda_index), (ptr->tda_next) ? ',' : ' ' );
			ptr = ptr->tda_next; 
	}
	puts("} \n");
}


void s_printConjuntos(tda_base_t **C1,tda_base_t**C2)
{
	s_printConjunto(C1);
	s_printConjunto(C2);
}

int s_cardinal(tda_base_t **conj)
{
	return tda_base_len(conj); 
}

bool s_pertenece(tda_base_t **conj, String elem)
{
	bool cond = (*conj && (*conj)->tda_next);
	tda_base_p tmp=tda_get_head(conj);
	for(;cond && tmp;){
		cond = ( (((*conj)->tda_type >= TDA_CIRCULAR_LIST) && (tmp != tda_get_head(conj))) || ( ((*conj)->tda_type < TDA_CIRCULAR_LIST) && tmp));
		if( !strcmp(((String) tmp->tda_data ),elem) ) return true;
		tmp = tmp->tda_next;
	}
	return false;
}

tda_base_t *s_union(tda_base_t **conj1, tda_base_t **conj2, tda_type_t list_type)
{
	bool cond = (*conj1 && (*conj1)->tda_next);
	tda_base_p p1=tda_get_head(conj1);
	tda_base_p p2=tda_get_head(conj2);
	tda_base_t *retlist=NULL;

	tda_set_type(&retlist,list_type);

	for(;cond && p1;){
		cond = (  (list_type >= TDA_CIRCULAR_LIST) && (p1 != tda_get_head(conj1)) ) || (  (list_type < TDA_CIRCULAR_LIST) && p1 );
		s_agregarElemento(&retlist,((String)p1->tda_data),STRING_MAX);
		p1 = p1->tda_next;
	}

	cond = (*conj2 && (*conj2)->tda_next);

	for(;cond && p2;){
		cond = ( (list_type >= TDA_CIRCULAR_LIST) && (p2 != tda_get_head(conj2)) ) || ( (list_type < TDA_CIRCULAR_LIST) && p2 );
		if(!s_pertenece(conj1,((String)p2->tda_data))) s_agregarElemento(&retlist,((String)p2->tda_data), STRING_MAX);
		p2 = p2->tda_next;
	}
	return retlist;
}

tda_base_t *s_interseccion(tda_base_t **conj1, tda_base_t **conj2, tda_type_t list_type)
{
	bool cond = (*conj1 && (*conj1)->tda_next);
	tda_base_p p1=tda_get_head(conj1);
	tda_base_t *retlist=NULL;

	tda_set_type(&retlist,list_type);

	for(;cond && p1;){
		cond = ( (list_type >= TDA_CIRCULAR_LIST) && (p1 != tda_get_head(conj1)) ) || ( (list_type < TDA_CIRCULAR_LIST) && p1 );
		if(s_pertenece(conj2, ((String)p1->tda_data))) s_agregarElemento(&retlist, ((String)p1->tda_data), STRING_MAX);
		p1 = p1->tda_next;
	}
	return retlist;
}

tda_base_t *s_diferencia(tda_base_t **conj1, tda_base_t **conj2, tda_type_t list_type)
{
	bool cond = (*conj1 && (*conj1)->tda_next);
	tda_base_p p1=tda_get_head(conj1);
	tda_base_t *retlist=NULL;

	tda_set_type(&retlist,list_type);

	for(;cond && p1;){
		cond = ( (list_type >= TDA_CIRCULAR_LIST) && (p1 != tda_get_head(conj1)) ) || ( (list_type < TDA_CIRCULAR_LIST) && p1 );
		if(!s_pertenece(conj2, ((String)p1->tda_data))) s_agregarElemento(&retlist, ((String)p1->tda_data),STRING_MAX);
		p1 = p1->tda_next;
	}
	return retlist;
}

tda_base_t *s_inclusion(tda_base_t **conj1, tda_base_t **conj2, tda_type_t list_type)
{
	tda_base_t *retlist=NULL;

	char mark = SUBCONJ_START;
	tda_set_type(&retlist,list_type);
	tda_base_add_all(&retlist,conj1);
	tda_base_add(&retlist,&mark);
	tda_base_add_all(&retlist, conj2);
	tda_base_add(&retlist,&mark);

	return retlist;
}

static void ask_agregar(tda_base_t **conj, tda_base_t **c2)
{
	char word[STRING_MAX];
	memset(word,0,STRING_MAX);
	int ncon;
	printf("   - Inserte el numero de conjunto al que desea agregar (0/1): "); scanf("%d",&ncon);
	printf("Inserte palabra: "); scanf("%s",word);

	switch(ncon){
		case 0:
			s_agregarElemento(conj,word,STRING_MAX);	
			break;
		case 1:
			s_agregarElemento(c2,word,STRING_MAX);
			break;
		}
}

void s_verificarPertenencia(tda_base_t **conj, tda_base_t **c2, tda_type_t listype)
{
	char add=0;
	int op=1,ncon, card;
	char word[STRING_MAX];
	do {
		clear();
		s_printConjuntos(conj,c2);
		printf("\nInserte [0:Salir, 1:Verificar, 2:Unir, 3: Agregar, 4: Interseccion, 5: Diferencia, 6: Inclusion, 7: Cardinalidad] = "); scanf("%d",&op);
		if(op==1){
			printf("Inserte numero de conjunto (0/1): "); scanf("%d",&ncon);
			printf("\nInserte palabra: "); scanf("%s",word);
			printf("\t-> %s pertenece a C: %s\n",word, ( (!ncon) ? s_pertenece(conj,word) : s_pertenece(c2,word)  ) ? "Verdadero" : "Falso"); 
			fflush(stdin); fflush(stdout);
			printf(" Desea agregar una nueva palabra a algun conjunto (y/N)? "); scanf("%c",&add);
			if(add=='y' || add=='Y') ask_agregar(conj,c2);
		} else if(op==2) *conj = s_union(conj,c2,listype);
		else if(op==3) ask_agregar(conj,c2);
		else if(op==4) *conj = s_interseccion(conj,c2,listype);
		else if(op==5) *conj = s_diferencia(conj,c2,listype);
		else if(op==6){
				printf("Inserte numero de conjunto destino (0/1): "); scanf("%d", &ncon);
				switch(ncon){
				case 0:
				*conj = s_inclusion(conj,c2,listype);
				break;		
				case 1:
				*c2 = s_inclusion(c2,conj,listype);
				break;
			}	 
		} else if(op==7){
			printf("Inserte el numero de conjunto al que desea calcular la Cardinalidad (0/1): "); scanf("%d", &ncon);
			switch(ncon){
				case 0:
				card = s_cardinal(conj);
				break;
				case 1:
				card = s_cardinal(c2);
				break;
			}
			printf("Cardinalidad de C[%d] = %d\n", ncon+1, card);
			pause();
		}
	} while(op);
}

void les_problema9()
{
	system("color 9");
	tda_simple_list_t *conjunto=NULL, *c2=NULL;
	tda_set_type(&conjunto, TDA_SIMPLE_LIST);
	tda_set_type(&c2, TDA_SIMPLE_LIST);
	s_agregarElementos(&conjunto,&c2);
	puts("Conjunto 1");
	tda_tshow(&conjunto,STRING); puts("Conjunto2");
	tda_tshow(&c2,STRING); pause();
	s_printConjuntos(&conjunto,&c2);
	printf("\nCardinalidad del conjunto 1: %d\n", s_cardinal(&conjunto) );
	printf("\nCardinalidad del conjunto 2: %d\n", s_cardinal(&c2) );
	s_verificarPertenencia(&conjunto,&c2,TDA_SIMPLE_LIST);
}


void led_problema9()
{
	system("color 9");
	tda_double_list_t *conjunto=NULL, *c2=NULL;
	tda_set_type(&conjunto, TDA_DOUBLE_LIST);
	tda_set_type(&c2, TDA_DOUBLE_LIST);
	s_agregarElementos(&conjunto,&c2);
	s_printConjuntos(&conjunto,&c2);
	tda_tshow(&conjunto,STRING); pause();
	tda_tshow(&c2, STRING); pause();
	printf("\nCardinalidad del conjunto 1: %d\n", s_cardinal(&conjunto) );
	printf("\nCardinalidad del conjunto 2: %d\n", s_cardinal(&c2) );
	s_verificarPertenencia(&conjunto,&c2,TDA_DOUBLE_LIST);
}

void lec_problema9()
{
	system("color 9");
	tda_simple_circle_list_t *conjunto=NULL, *c2=NULL;
	tda_set_type(&conjunto, TDA_CIRCULAR_LIST);
	tda_set_type(&c2, TDA_CIRCULAR_LIST);
	s_agregarElementos(&conjunto,&c2);
	s_printConjuntos(&conjunto,&c2);
	tda_tshow(&conjunto,STRING); pause();
	tda_tshow(&c2,STRING); pause();
	printf("\nCardinalidad del conjunto 1: %d\n", s_cardinal(&conjunto) );
	printf("\nCardinalidad del conjunto 2: %d\n", s_cardinal(&c2) );
	s_verificarPertenencia(&conjunto,&c2,TDA_CIRCULAR_LIST);
}


void ledc_problema9()
{
	system("color 9");
	tda_double_circle_list_t *conjunto=NULL, *c2=NULL;
	tda_set_type(&conjunto, TDA_DOUBLE_CIRCULAR_LIST);
	tda_set_type(&c2, TDA_DOUBLE_CIRCULAR_LIST);
	s_agregarElementos(&conjunto,&c2);
	s_printConjuntos(&conjunto,&c2);
	tda_tshow(&conjunto,STRING); pause();
	tda_tshow(&c2,STRING); pause();
	printf("\nCardinalidad del conjunto 1: %d\n", s_cardinal(&conjunto) );
	printf("\nCardinalidad del conjunto 2: %d\n", s_cardinal(&c2) );
	s_verificarPertenencia(&conjunto,&c2,TDA_DOUBLE_CIRCULAR_LIST);
}

