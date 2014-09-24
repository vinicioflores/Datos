#include "cap9.h"

struct nodo_polinomio
{
	bool signo;
	double coeficiente;
	int exponente;
};

void print_pols(tda_simple_list_t **pol)
{
	struct nodo_polinomio *np = NULL;
	tda_base_t *p = *pol;

	while(p){
		if(p->tda_data) { 
			np = (struct nodo_polinomio *) p->tda_data;
			if(np->exponente > 0) printf("%c%2.2lfx**%d", (np->signo) ? '-' : '+',  np->coeficiente, np->exponente);
			else printf("%c%2.2lf", (np->signo) ? '-' : '+',  np->coeficiente);
		}

		p = p->tda_next;
	}
	puts("");
}

void proc_pl(tda_simple_list_t **head, int grado)
{
	int i_added=0;
	struct nodo_polinomio pl;
	tda_base_t *p = NULL;
	tda_base_destroy(head);
	while(grado >= 0){
		printf("Inserte coeficiente de X**%d: ", grado);
		scanf("%lf", &pl.coeficiente);
	
		do {
			printf("Inserte el signo de %lf (1/negativo, 0/positivo): ", pl.coeficiente);
			scanf("%d", &pl.signo);
		} while(pl.signo < 0 && pl.signo > 1);

		pl.exponente = grado;
		i_added = tda_base_add(head, malloc(sizeof(struct nodo_polinomio)) );
		p = tda_base_search(head,i_added);
		memcpy(p->tda_data, (const void *)(&pl), sizeof(struct nodo_polinomio) );

		grado--;
	}
}

void pl_solve(tda_simple_list_t **head, double step_x, double lim_x)
{
	clear();
	print_pols(head);
	puts("");
	double coef,res,xval;
	coef = res = xval = 0;
	tda_base_t *p=NULL;
	struct nodo_polinomio *np=NULL;
	do {
		if(!(*head)) return;
		else {  
			if( (*head)->tda_next ) p = (*head)->tda_next; 
			else return;
		}
		while(p){
			np = (struct nodo_polinomio *) tda_base_getdata(head,p->tda_index);
			
			switch(np->signo){
				case true:
					coef = -(np->coeficiente);
					break;
				case false:
					coef = np->coeficiente;
					break;
			}
			
			res += (coef * pow(xval,np->exponente));
			p = p->tda_next;
		}
		printf("S[X=%3.3lf]: { %3.3lf }\n", xval, res);
		res = 0;
		xval += step_x;
	} while(xval <= lim_x);
}

/************** Cuerpo del problema **/
void les_problema3()
{
	#ifdef _WIN32
	system("color 3");
	#endif

	printf("Problema #9.3 Pagina 308, Resolucion de polinomios con lista enlazadas simples \n\n");
	tda_simple_list_t *pl_list=NULL;
	int grado=0;
	bool salir = false;
	
	while(salir==false){
		printf("\nInserta el grado de un polinomio nuevo , -1 para imprimir tabla o 0 para salir: ");
		scanf("%d", &grado);

		if(!grado) salir = true;
		else if(grado == -1){
			if(pl_list && pl_list->tda_next){ pl_solve(&pl_list, 0.5, 5.0); if(pl_list) tda_base_destroy(&pl_list); }
			else printf("No hay un polinomio para resolver ... \n");
		}
		else {
			tda_set_type(&pl_list, TDA_SIMPLE_LIST);
			proc_pl(&pl_list,grado);
			tda_base_show(&pl_list);
		}
	}
}

void led_problema3()
{
	#ifdef _WIN32
	system("color 5");
	#endif

	printf("Problema #9.3 Pagina 308, Resolucion de polinomios con listas doblemente enlazadas \n\n");
	tda_double_list_t *pl_list=NULL;
	int grado=0;
	bool salir = false;
	
	while(salir==false){
		printf("\nInserta el grado de un polinomio nuevo , -1 para imprimir tabla o 0 para salir: ");
		scanf("%d", &grado);

		if(!grado) salir = true;
		else if(grado == -1){
			if(pl_list && pl_list->tda_next){ pl_solve(&pl_list, 0.5, 5.0); if(pl_list) tda_base_destroy(&pl_list); }
			else printf("No hay un polinomio para resolver ... \n");
		}
		else {
			tda_set_type(&pl_list, TDA_DOUBLE_LIST);
			proc_pl(&pl_list,grado);
			tda_base_show(&pl_list);
		}
	}
}
