#include "cap9.h"

void showNum(tda_base_t **longn);
void fillNum(tda_base_t **longInt)
{
	int maxdig=0,counter=1,dig=0;
	printf("Introduzca el numero de digitos del entero (> 30 preferiblemente):  ");
	scanf("%d", &maxdig);

	while(maxdig){
		printf("Inserte digito #%d: ", counter); scanf("%d",&dig);
		tda_base_savedat(longInt, (void *)(&dig), tda_base_insf(longInt,NULL), sizeof(dig) );
		counter++;
		maxdig--;
	}

	//#ifdef _WIN32;  No es necesario añadir esto porque la funcion clear() que esta implementada ya lo hace a lo interno
	// Si no estamos en un sistema Windows entonces no hace nada
	clear();
	//#endif
	printf("\nN=");
	showNum(longInt);
	puts("\n\nVolcado de lista en memoria\n");
	tda_tshow(longInt, INT);
}

void acommodate(tda_base_t **n1, tda_base_t **n2)
{
	tda_base_t **pt=NULL;
	int nulldig = 0;
	int count=0;
	int ln1 = tda_base_len(n1);
	int ln2 = tda_base_len(n2);

	if(ln1 > ln2){
		count = ln1-ln2;
		pt = n2;
	} else {
		count = ln2-ln1;
		pt = n1;
	}

	while(count){
		tda_base_savedat(pt, &nulldig, tda_base_insf(pt,NULL), sizeof(nulldig));
		count--;
	}
}

void longSum(tda_base_t **longn1, tda_base_t **longn2)
{
	int sumadig=0;
	tda_base_p pn1, pn2;
	pn1 = tda_get_head(longn1);
	pn2 = tda_get_head(longn2);

	for(; pn1 && pn2; ){
		sumadig = (tda_iget(longn1,pn1->tda_index) + tda_iget(longn2, pn2->tda_index));
		tda_base_savedat(longn1, (void *)(&sumadig), pn1->tda_index, sizeof(sumadig) );
		pn1 = pn1->tda_next;
		pn2 = pn2->tda_next;
	}
	printf("\nSuma= ");
	showNum(longn1);
	puts("");
}

void showNum(tda_base_t **longn)
{
	tda_base_p pn= tda_get_head(longn);

	for(;pn;){
		printf("%d", tda_iget(longn, pn->tda_index) );
		pn = pn->tda_next;
	}
}


void les_problema11()
{
	tda_simple_list_t *enteroLargo1=NULL;
	tda_simple_list_t *enteroLargo2=NULL;

	tda_set_type(&enteroLargo1, TDA_SIMPLE_LIST);
	tda_set_type(&enteroLargo2, TDA_SIMPLE_LIST);

	fillNum(&enteroLargo1);
	fillNum(&enteroLargo2);
	acommodate(&enteroLargo1,&enteroLargo2);
	showNum(&enteroLargo1); printf(" + "); showNum(&enteroLargo2);
	puts("\n|----------------------------------------------------------------------|\n");

	longSum(&enteroLargo1, &enteroLargo2); /* Realiza la suma de los dos enteros largos y el
												* resultado lo almacena en el entero largo 1 */
}

void led_problema11()
{
	tda_double_list_t *enteroLargo1=NULL;
	tda_double_list_t *enteroLargo2=NULL;

	tda_set_type(&enteroLargo1, TDA_DOUBLE_LIST);
	tda_set_type(&enteroLargo2, TDA_DOUBLE_LIST);

	fillNum(&enteroLargo1);
	fillNum(&enteroLargo2);
	acommodate(&enteroLargo1,&enteroLargo2);
	showNum(&enteroLargo1); printf(" + "); showNum(&enteroLargo2);
	puts("\n|----------------------------------------------------------------------|\n");

	longSum(&enteroLargo1, &enteroLargo2); /* Realiza la suma de los dos enteros largos y el
												* resultado lo almacena en el entero largo 1 */
}

void lec_problema11()
{
	tda_simple_circle_list_t *enteroLargo1=NULL;
	tda_simple_circle_list_t *enteroLargo2=NULL;

	tda_set_type(&enteroLargo1, TDA_CIRCULAR_LIST);
	tda_set_type(&enteroLargo2, TDA_CIRCULAR_LIST);

	fillNum(&enteroLargo1);
	fillNum(&enteroLargo2);
	acommodate(&enteroLargo1,&enteroLargo2);
	showNum(&enteroLargo1); printf(" + "); showNum(&enteroLargo2);
	puts("\n|-------------------------------------------------------------------------|\n");

	longSum(&enteroLargo1, &enteroLargo2); /* Realiza la suma de los dos enteros largos y el
												* resultado lo almacena en el entero largo 1 */
}

void ledc_problema11()
{
	tda_double_circle_list_t *enteroLargo1=NULL;
	tda_double_circle_list_t *enteroLargo2=NULL;

	tda_set_type(&enteroLargo1, TDA_DOUBLE_CIRCULAR_LIST);
	tda_set_type(&enteroLargo2, TDA_DOUBLE_CIRCULAR_LIST);

	fillNum(&enteroLargo1);
	fillNum(&enteroLargo2);
	acommodate(&enteroLargo1,&enteroLargo2);
	showNum(&enteroLargo1); printf(" + "); showNum(&enteroLargo2);
	puts("\n|------------------------------------------------------------------------|\n");

	longSum(&enteroLargo1, &enteroLargo2); /* Realiza la suma de los dos enteros largos y el
												* resultado lo almacena en el entero largo 1 */
}

