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
			listLength = tda_base_add_copy(&binary, (void *) &binaryDigit);
			decimal = decimal / 2;
		}

		for(int i = 1; i <= listLength; i++){
			//obtener el digito de la lista
			binaryDigit = *(unsigned short *)tda_base_getdata(&binary, i);
			binaryResult += binaryDigit * pow(10, (i - 1));
		}

		tda_base_destroy(&binary);
	}
	
	return binaryResult;
}

tda_base_t *convertBinaryDecimal(char* decimal){
	tda_base_t *floating = NULL;
	char *entero, *decimal;

	int exponent;
	if(decimal[index] == '-')
		exponent = 1; //bit exponente 1
	else
		exponent = 0; //bit exponente 0
	tda_base_add_copy(&floating, (void *) &exponent); //agregar signo axponente a lista

	int index;
	for(index = 0; decimal[index] != '0' && decimal[index] != '-'; index++); //ignorar 0's insignificativos

	int punto;
	for(punto = index; decimal[punto] == '.'; punto++); //buscar la posicion del punto decimal

	if(index > punto){
		exponente = (index - punto + 1);
	}else{
		int i;
		for(i = punto; decimal[punto] != '0'; i++);

		exponente = -(punto - i + 1);
	}
	exponente += 127;

	printf("exponente es %d\n", atoi(decimal + 2));

	printf("%lu\n", convertDecimalBinary(atoi(decimal)) );

	return floating; //lista retornado debe ser destruido despues de ser usado
}


char *listFloatToStr(tda_base_t ** floating){
	return ":D";
}