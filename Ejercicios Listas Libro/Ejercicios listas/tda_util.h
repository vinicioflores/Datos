/**
	Archivo de cabecera de las funciones de
	utilidad del TDA universal

	Vinicio Flores, 2014
	Tecnológico de Costa Rica

**/

#ifndef __TDA_UTIL_H
#define __TDA_UTIL_H

#ifndef __TDA_CORE_H
	#include "tda_core.h"
#endif

typedef enum {CHAR,INT,DOUBLE,FLOAT,SCI,IEEE,POINTER,STRING} tda_data_t;
void tda_randgen(tda_base_t **,int,int);	/* Genera una lista enlazada doble de n elementos con numeros aleatorios dentro del rango dado */
void tda_tshow(tda_base_t**,tda_data_t);

/* Lectura y conversión de datos VOID */
char tda_cget(tda_base_t **,int);
int tda_iget(tda_base_t **,int);
float tda_fget(tda_base_t **,int);
double tda_lfget(tda_base_t **,int);
char *tda_sget(tda_base_t **,int);
void pause();
void clear();
void clpause();

#endif

	

