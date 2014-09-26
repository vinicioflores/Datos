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
	int opt;
	puts("Pasajeros de la Aerolinea\n\n");
	printf("0) Salir\n"
	"1) Insertar pasajero nuevo\n"
	"2) Eliminar pasajero de lista\n");
	struct pasajero np;

	switch(opt){
		case 0:
			exit(0);
			break;
		case 1:
			fflush(stdin); fflush(stdout);
			printf("Inserte nombre de pasajero nuevo: "); scanf("%s", np.nombre);
			printf("Inserte la edad del pasajero nuevo; "); scanf("%d",&np.edad);
			printf("Inserte el numero de telefono del pasajero;"); scanf("%d",&np.tel);
			printf("Inserte su cedula de identificacion: "); scanf("%d", &np.cedula);
			tda_base_savedat(pasajeros, &np, tda_base_add(pasajeros, NULL), sizeof(np));
			break;
		case 2:
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