#include <stdio.h>
#include <string.h>

#ifndef _binaryCalc_H
#define _binaryCalc_H

//programa es dependente del TDA
#include "tda_core.h"

//estandard numeros flotantes IEEE "single precision" Binary32
#define BITS 32
#define EXPONENT 8
#define MANTISA 23 


//retorna una lista que contiene un numero decimal en forma binario32
tda_base_t *convertBinaryDecimal(char decimal[]);
//retona referencia a una lista que es una lista formado por los
//elementos de una lista del tda con tipo short
void listToStr(tda_base_t * shortList, char *str, int listSize);
void printFloa(tda_base_t * floating);

#endif
