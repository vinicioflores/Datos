#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef _binaryCalc_H
#define _binaryCalc_H

//programa es dependente del TDA
#include "tda_core.h"

#define PRECISION 32
#define EXPO_SLOTS 8

/*retorna por referencia dos ultimos chars que contiene el flotante convertido
primer char es el exponent balancead y el segundo es la mantissa precision varia
en base del tamano del numero binario entero */
void convertDecimalFloating(char *, char *, char**, char**);
//retona referencia a una lista que es una lista formado por los
//elementos de una lista del tda con tipo short
void listToStr(tda_base_t * shortList, char *str, int listSize);
//valor en decimal lo retorna por referencia es "wholenumber" y "fraction"
float convertFloatToDeci(char exponent[], char mantissa[]);

#endif
