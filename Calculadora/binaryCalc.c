#include "binaryCalc.h"

unsigned long convertDecimalBinary(unsigned int decimal){
	//resultado de la conversion
	unsigned long binaryResult = 0;
	unsigned short binaryDigit;

	unsigned int listLength;
	tda_base_t *binary = NULL;

	//si decimal no es 0
	if(decimal){
		for(;decimal != 0;){
			binaryDigit = decimal % 2;
			listLength = tda_base_add(&binary, (void *) &binaryDigit);
			decimal = decimal / 2;
		}

		tda_base_show(&binary);

		//recorer lista de atras para delante
		for(; listLength; listLength--){
			printf("%d binario\n", *(int *)tda_base_getdata(&binary, listLength));
		}

		tda_base_destroy(&binary);
	}

	return binaryResult;
}
