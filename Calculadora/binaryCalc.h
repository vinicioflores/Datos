#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef _binaryCalc_H
#define _binaryCalc_H

//programa es dependente del TDA
#include "tda_core.h"

//retorna una lista que contiene un numero decimal en forma binario32
void convertBinaryDecimal(char *, char *, int precision, char**, char**);
//retona referencia a una lista que es una lista formado por los
//elementos de una lista del tda con tipo short
void listToStr(tda_base_t * shortList, char *str, int listSize);

#endif
