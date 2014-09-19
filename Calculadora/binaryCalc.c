#include "binaryCalc.h"

/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un entero decimal a binario */
static tda_base_t *convertDecimalFractionBinary(float deciFraction);
/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un entero decimal a binario */
static tda_base_t *convertDecimalBinary(unsigned int decimal);


tda_base_t *convertDecimalBinary(unsigned int decimal){
	//resultado de la conversion
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
	}
	
	return binaryResult;
}

//acepta un float fracionario como "0.1" y retorna una referencia a la lista
// que contiene el valor del fraccion como **SHORT***
tda_base_t *convertDecimalFractionBinary(float deciFraction){
	tda_base_t *binaryFraction = NULL;
	short bit0 = 0, bit1 = 1;

	for(int i = 0; i < MANTISA; i++){
		deciFraction = deciFraction * 2;
		if((int) deciFraction){
			deciFraction -= (int) deciFraction;
			tda_base_add_copy(&binaryFraction, (void *) &bit1);
		}else{
			tda_base_add_copy(&binaryFraction, (void *) &bit0);
		}
	}//fin for



	//retona refenrencia a lista, tipo dato es short
	return binaryFraction;
}

tda_base_t *convertBinaryDecimal(char decimal[]){
	tda_base_t *floating = NULL;
	tda_base_t *binaryFraction = NULL;

	int index = 0;
	unsigned long wholeNum; //entero
	float fraction; //parte fracionaria
	unsigned int exponent;

	short sign = 0; //sign
	if(decimal[index] == '-') //si es un numero negativo
			sign = 1;
	//agregar signo axponente a lista
	tda_base_add_copy(&floating, (void *) &sign); 

	wholeNum = (long) atoi(decimal + sign);
	wholeNum = convertDecimalBinary(wholeNum);

	fraction = atof(decimal + sign) - wholeNum;
	binaryFraction = convertDecimalFractionBinary(fraction);
	
	printf("whoeNum is: %lu\n", wholeNum);

	if(wholeNum == 1){//si numero es 1.XXXX
		exponent = 0;
	}else if(wholeNum == 0){//si numero es menor a 1
		for(int i = 1; i <= tda_get_end(&binaryFraction); i++){
			//cantidad de veces correr punto decimal a la izquierda
			if(*(short *) tda_base_getdata(&binaryFraction, i))
				exponent = -(i - 1);
		}
	}else{ //si numero es mayor a 1
		exponent = sizeof(wholeNum) / sizeof(long) - 1;
		printf("here exponent is %d\n", exponent);
	}
	printf("exponent is %d\n", exponent);


	//printf("wholeNum is %d\n", wholeNum);
	//printf("fraction is %f\n", fraction);

	//printf("wholeNum in binary %d\n", convertDecimalBinary(atoi(wholeNum)) );

	//destruir la lista de la parte fracionaria binario
	tda_base_destroy(&binaryFraction);

	return floating; //lista retornado debe ser destruido despues de ser usado
} 


char *listFloatToStr(tda_base_t ** floating){
	return ":D";
} 