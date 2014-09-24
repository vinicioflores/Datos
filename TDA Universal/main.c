/* Archivo de pruebas con el TDA principal (base) 

	Estructuras de Datos, II Semestre
	Vinicio Flores Hernández, 2014
	Tecnológico de Costa Rica
*/

// Permite obtener una mejor comprensión del
// TDA base y su capacidad para almacenar cualquier
// tipo de objeto en cada uno de sus nodos

#include "tda_stack.h"
#include "tda_util.h"

void testbin();
void testlists();
void testpila();
void testrand();

int main(void)
{	
	testlists();
	testpila();
	testrand();

	testbin();
	return 0;
}


void testlists()
{
	String s = "Costa Rica";
	double k = 4.4545;
	char c = 'f';
	int d = 0xF;
	float f = 31416178667800012345676848754.000117774445554348;

	tda_base_t *list = NULL; /* Es de SUMA IMPORTANCIA que la lista siempre se inicialize con NULL */

	tda_set_type(&list,TDA_CIRCULAR_LIST);  /* Aqui la convierto en circular ya que en este TDA al principio es una lista
											 doblemente enlazada */
	int ik  = tda_base_insf(&list,  (void *)(&k)); 
	int ic  = tda_base_add(&list,   (void *)(&c));
	int id  = tda_base_add(&list,   (void *)(&d));
	int is  = tda_base_ins(&list,id,(void *)(s));
	int ifl = tda_base_add(&list,   (void *)(&f));

	printf("lista0 is empty? %s\n", (tda_base_isempty(&list)) ? "True" : "False" );
	system("color 2");
	
	puts("\n\tTDA Lista \n");
	
	printf("ik:%d\tk=%10lf\n",ik,*( (double *)(tda_base_getdata(&list,ik))));
	printf("ic:%d\tk=%10c\n",ic,	tda_cget(&list,ic));
	printf("ii:%d\tk=%10d\n",id,	tda_iget(&list,id));
	printf("is:%d\tk=%s\n",is,		tda_sget(&list,is));
	printf("if:%d\tk=%10E\n\n",ifl,*( (float *)(tda_base_getdata(&list,ifl))));

	tda_base_show(&list);
	tda_base_destroy(&list);

	printf("lista0 is empty? %s\n", (tda_base_isempty(&list)) ? "True" : "False" );
	system("PAUSE");
	system("cls");

}

void testpila()
{
	char c0 = 'A';
	float c1 = 2.8557565656;
	int  d0 = 90;
	char c2 = 'g';
	char *s0 = "Hola mundo de pilas!!!! ";

	tda_stack_p pila0=NULL;

	system("color 4");
	printf("pila0 is empty? %s\n", (tda_stack_isempty(&pila0)) ? "True" : "False" );
	puts("\n\tTDA Pila \n");
	
	tda_push(&pila0, (void *)(&c0));
	tda_push(&pila0, (void *)(&c1));
	tda_push(&pila0, (void *)(&d0));
	tda_push(&pila0, (void *)(s0));
	tda_push(&pila0, (void *)(&c2));

	printf("pila0 is empty? %s\n", (tda_stack_isempty(&pila0)) ? "True" : "False" );

	tda_base_show(&pila0);

	printf("c2=%10c\n",     *((char *) tda_pop(&pila0) ));
	printf("s0=%s\n",    	 ((char *) tda_pop(&pila0) ));
	printf("d0=%10d\n",     *((int *)  tda_pop(&pila0) ));
	printf("c1=%10e\n",     *((float *) tda_pop(&pila0) ));
	printf("c0=%10c\n",     *((char *)  tda_pop(&pila0) ));

	tda_stack_destroy(&pila0);
	printf("pila0 is empty? %s\n", (tda_stack_isempty(&pila0)) ? "True" : "False" );

	system("PAUSE");
	system("cls");
}


void testrand()
{
	tda_base_t *sp=NULL;  // Todo puntero del TDA debe estar inicializado en NULL
	
	#ifdef _WIN32
		system("cls");
		system("color 5");
	#endif
	
	tda_randgen(&sp,15,10);
	tda_set_type(&sp,TDA_CIRCULAR_LIST);
	system("cls");
	tda_base_show(&sp);
	system("pause");
}

void testbin()
{
	tda_stack_p sp=NULL;
	float fn = 356.1457;
	int dig = 0;

	printf("sp is empty? %s\n", (tda_stack_isempty(&sp)) ? "True" : "False" );

	do {
		dig = (int)fn%10;
		tda_push(&sp, (void*)(&dig) );
		fn = fn/10;
		printf("fn:%d\n",(int)fn);
	} while(fn);

	tda_stack_show(&sp);
	system("pause");
}

