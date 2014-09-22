/* Archivo de pruebas con el TDA principal (base) 

	Estructuras de Datos, II Semestre
	Vinicio Flores Hernández, 2014
	Tecnológico de Costa Rica
*/

// Permite obtener una mejor comprensión del
// TDA base y su capacidad para almacenar cualquier
// tipo de objeto en cada uno de sus nodos

#include "tda_stack.h"


int main(void)
{	
	double k = 4.4545;
	char c = 'Z';
	int d = 0xF;
	char *s = "Costa Rica";
	float f = 31416178667800012345676848754.000117774445554348;

	tda_base_t *list = NULL; /* Es de SUMA IMPORTANCIA que la lista siempre se inicialize con NULL */

	int ik  = tda_base_insf(&list,(void *)(&k)); 
	int ic  = tda_base_add(&list,(void *)(&c));
	int id  = tda_base_add(&list,(void *)(&d));
	int is  = tda_base_ins(&list,id,(void *)(s));
	int ifl = tda_base_add(&list, (void *)(&f));

	tda_set_type(&list,TDA_CIRCULAR_LIST);
	system("color 2");
	
	puts("\n\tTDA Lista \n");
	printf("ik:%d\tk=%10lf\n",ik,   *((double *) tda_base_getdata(&list,ik)));
	printf("ic:%d\tc=%10c\n", ic,     *((char *) tda_base_getdata(&list,ic)));
	printf("ii:%d\ti=%10d\n", id,      *((int *) tda_base_getdata(&list,id)));
	printf("is:%d\ts=%s\n", is,   	   ((char *) tda_base_getdata(&list,is)));
	printf("if:%d\tf=%10e\n\n", ifl, *((float *) tda_base_getdata(&list,ifl)));
	tda_base_show(&list);
	tda_base_destroy(&list);
	system("PAUSE");
	system("cls");

	char c0 = 'A';
	float c1 = 2.8557565656;
	int  d0 = 90;
	char c2 = 'g';
	char *s0 = "Hola mundo de pilas!!!! ";


	puts("\n\tTDA Pila \n");
	
	tda_stack_p pila0=NULL;
	
	printf("pila0 is empty? %s\n", (tda_stack_isempty(&pila0)) ? "True" : "False" );
	tda_push(&pila0, (void *)(&c0));
	tda_push(&pila0, (void *)(&c1));
	tda_push(&pila0, (void *)(&d0));
	tda_push(&pila0, (void *)(s0));
	tda_push(&pila0, (void *)(&c2));

	printf("pila0 is empty? %s\n", (tda_stack_isempty(&pila0)) ? "True" : "False" );

	tda_base_show(&pila0);

	printf("c2=%10c\n",     *((char *) tda_pop(&pila0) ));
	printf("s0=%s\n",     ((char *) tda_pop(&pila0) ));
	printf("d0=%10d\n",     *((int *) tda_pop(&pila0) ));
	printf("c1=%10e\n",     *((float *) tda_pop(&pila0) ));
	printf("c0=%10c\n",     *((char *)  tda_pop(&pila0) ));

	tda_stack_destroy(&pila0);
	printf("pila0 is empty? %s\n", (tda_stack_isempty(&pila0)) ? "True" : "False" );

	system("PAUSE");
	system("cls");

	return 0;
}


