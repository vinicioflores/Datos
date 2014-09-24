#include "cap9.h"

void les_problema1()
{
	#ifdef _WIN32
	system("color 2");
	#endif

	int rango,n,top,dat,i=1;
	rango = top = n = dat = 0;
	tda_simple_list_t* list,*tmp,*next;
	list = tmp = next = NULL;
	tda_set_type(&list,TDA_SIMPLE_LIST);
	printf("Inserte el numero de elementos a crear: "); scanf("%d",&n);
	printf("Inserte el rango de los valores a generar: "); scanf("%d", &rango);
	puts("");
	tda_randgen(&list,n,rango);
	tda_tshow(&list,INT);
	puts("");
	printf("Inserte tope de valores numericos: ");
	scanf("%d",&top);
	tmp = tda_get_head(&list);
	
	if(tmp){
		while(tmp->tda_next){
			dat = tda_iget(&list,i); /* Devuelve el valor del campo dato y le hace un cast a entero */
			next = tmp->tda_next;
			if(dat >= top) tda_base_delete(&list,i);
			if(tmp) tmp = next;
			i++;
		}
	}

	//clear();
	printf("Lista aleatoria despues de eliminar los elementos > %d\n\n", top);
	tda_tshow(&list,INT); pause();
	tda_base_destroy(&list);
}

void led_problema1()
{
	#ifdef _WIN32
	system("color 6");
	#endif

	int rango,n,top,dat,i=1;
	rango = top = n = dat = 0;
	tda_double_list_t* list,*tmp,*last=NULL;
	list = tmp = NULL;
	tda_set_type(&list,TDA_DOUBLE_LIST);
	printf("Inserte el numero de elementos a crear: "); scanf("%d",&n);
	printf("Inserte el rango de los valores a generar: "); scanf("%d", &rango);
	puts("");
	tda_randgen(&list,n,rango);
	tda_tshow(&list,INT);
	puts("");
	printf("Inserte tope de valores numericos: ");
	scanf("%d",&top);
	tmp = tda_get_head(&list);
	
	while(tmp){
		dat = tda_iget(&list,i); /* Devuelve el valor del campo dato y le hace un cast a entero */
		last = tmp;
		if(dat >= top) tda_base_delete(&list,i);
		tmp = tmp->tda_next;
		i++;
	}

	//clear();
	printf("Lista aleatoria despues de eliminar los elementos > %d\n\n", top);
	tda_tshow(&list,INT); pause();
	tda_base_destroy(&list);
}

