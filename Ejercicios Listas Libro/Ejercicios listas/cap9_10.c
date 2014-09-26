#include "cap9.h"

#define MAXNAME			128

struct pasajero
{
	char nombre[MAXNAME];
	int edad;
	int tel;
	int cedula;
} pasajero;

void pasajeros_menu(tda_base_t **pasajeros, tda_base_t **endlist)
{
	clear();

	bool keep_seeking=true;
	int opt,tmpced;
	opt = tmpced = 0;
	struct pasajero np,*pd=NULL;
	tda_base_p p=NULL;


	puts("Pasajeros de la Aerolinea\n\n");
	printf("0) Salir\n"
	"1) Insertar pasajero nuevo\n"
	"2) Eliminar pasajero de lista\n"
	"3) Revisar lista\n");

	printf("Opcion: ");
	scanf("%d",&opt);

	clear();

	switch(opt){
		case 1:
			fflush(stdin); fflush(stdout);
			printf("Inserte nombre de pasajero nuevo: "); scanf("%s", np.nombre);
			printf("Inserte la edad del pasajero nuevo; "); scanf("%d",&np.edad);
			printf("Inserte el numero de telefono del pasajero "); scanf("%d",&np.tel);
			printf("Inserte su cedula de identificacion: "); scanf("%d", &np.cedula);
			tda_base_savedat(pasajeros, &np, tda_base_add(pasajeros, NULL), sizeof(np));
			pasajeros_menu(pasajeros, endlist);
			break;
		case 2:

			printf("Inserte el numero de identificacion (cedula) del pasajero: ");
			scanf("%d",&tmpced);

			p = tda_get_head(pasajeros);

			for(;p && keep_seeking;){
				pd = (struct pasajero *) p->tda_data;
				if(pd && pd->cedula == tmpced) keep_seeking = false;
				if(keep_seeking) p = p->tda_next;
			}

			if(pd->cedula == tmpced){
				tda_base_delete(pasajeros,p->tda_index);
				printf("Pasajero eliminado de la lista exitosamente!\n");
			} else printf("No se encontro el pasajero con la cedula indicada!\n");

			pause();
			pasajeros_menu(pasajeros, endlist);
			break;

		case 3:
			if(!(*pasajeros) || !((*pasajeros)->tda_next) ){ 
				printf("No hay pasajeros registrados ... \n");
				pause();
				pasajeros_menu(pasajeros, endlist);
				break;
			} 

			pd = NULL;
			p = tda_get_head(pasajeros);

			for(;p ||  (p != *pasajeros && (*pasajeros)->tda_type==TDA_CIRCULAR_LIST);){
				printf("Inf iter ... \n");
				pd = (struct pasajero *)  p->tda_data;
				if(pd){
					printf("Pasajero [%d]: \n\t"
							"Nombre: %s\n\t"
							"Cedula: %d\n\t"
							"Telefono: %d\n\t"
							"Edad: %d\n", p->tda_index, pd->nombre, pd->cedula, pd->tel, pd->edad);
				}
				p = p->tda_next;
			}

			if(pasajeros)
			{
				puts("");
				tda_base_show(pasajeros);
				puts("");
			}

			pause();
			pasajeros_menu(pasajeros, endlist);
			break;
		case 0:
			exit(0);
			break;
	}
}

void les_problema10()
{
	tda_simple_list_t *pasajeros=NULL;
	tda_simple_list_t *end = NULL;
	tda_set_type(&pasajeros,TDA_SIMPLE_LIST);
	end = pasajeros;
	pasajeros_menu(&pasajeros,&end);
}

void led_problema10()
{
	tda_double_list_t *pasajeros=NULL;
	tda_double_list_t *end = NULL;
	tda_set_type(&pasajeros,TDA_DOUBLE_LIST);
	end = pasajeros;
	pasajeros_menu(&pasajeros,&end);
}

void lec_problema10()
{
	tda_simple_circle_list_t *pasajeros=NULL;
	tda_simple_circle_list_t *end = NULL;
	tda_set_type(&pasajeros,TDA_CIRCULAR_LIST);
	end = pasajeros;
	pasajeros_menu(&pasajeros,&end);
}

void ledc_problema10()
{
	tda_double_circle_list_t *pasajeros=NULL;
	tda_double_circle_list_t *end = NULL;
	tda_set_type(&pasajeros,TDA_DOUBLE_CIRCULAR_LIST);
	end = pasajeros;
	pasajeros_menu(&pasajeros,&end);
}

