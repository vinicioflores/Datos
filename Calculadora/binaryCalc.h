#include <stdio.h>
#include <string.h>

#ifndef _binaryCalc_H
#define _binaryCalc_H

//programa es dependente del TDA
#include "tda_core.h"

//estandard numeros flotantes IEEE "single precision" Binary32
#define BITS 32;
#define SIGN 1;
#define EXPONENT 8
#define MANTISA 23;

//retorna un numero binario en base de un numero decimal sin signo
unsigned long convertDecimalBinary(unsigned int decimal);
//retorna una lista que contiene un numero decimal en forma binario32
tda_base_t *convertBinaryDecimal(char* decimal);

char *listFloatToStr(tda_base_t ** floating);

#endif
