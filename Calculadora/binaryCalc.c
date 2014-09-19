#include "binaryCalc.h"

/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un una francion decimal a binario */
static tda_base_t *convertDecimalFractionBinary(float deciFraction);
/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un un entero decimal a binario */
static tda_base_t *convertDecimalBinary(unsigned int decimal);

unsigned long listToLong(tda_base_t** shortList, int listSize);

//numero digitos en un numero
int nlen(unsigned int digit){
	for(int i = 1;;i++){
		if(digit < pow(10, i)){
			return i;
		}
	}
}

static tda_base_t *convertDecimalBinary(unsigned int decimal){
	unsigned short binaryDigit;

	tda_base_t *binary = NULL;

	//si decimal no es 0
	if(decimal){
		for(;decimal != 0;){
			binaryDigit = decimal % 2;
			tda_base_add_copy(&binary, (void *) &binaryDigit);
			decimal = decimal / 2;
		}
	}else{
		tda_base_add_copy(&binary, (void *) &decimal);
	}
	
	return binary;
}

//acepta un float fracionario como "0.1" y retorna una referencia a la lista
// que contiene el valor del fraccion como **SHORT***
static tda_base_t *convertDecimalFractionBinary(float deciFraction){
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
	tda_base_t *wholeNum = NULL;
	tda_base_t *balancedExponent = NULL;

	int index = 0;
	int wholeDeci; //parte entero
	float fractionDeci; //parte fracionaria
	unsigned int exponent;

	short sign = 0; //sign
	if(decimal[index] == '-') //si es un numero negativo
			sign = 1;
	//agregar signo axponente a lista
	tda_base_add_copy(&floating, (void *) &sign);

	//convertir parte entero a binario
	wholeDeci = (int) atoi(decimal + sign);
	wholeNum = convertDecimalBinary(wholeDeci);

	//convertir parte fracionario a binario
	fractionDeci = atof(decimal + sign) - (int) atoi(decimal + sign);
	binaryFraction = convertDecimalFractionBinary(fractionDeci);

	//encontrar digito antes del punto
	index = tda_get_end(&wholeNum);
	if(index == 1){//si parte entera solo tiene un digito
		short keyDigit = *(short*) tda_base_getdata(&wholeNum, index);

		if(keyDigit == 0){//si numero es menor a 1
			for(int i = 1; i <= tda_get_end(&binaryFraction); i++){
				//cantidad de veces correr punto decimal a la izquierda
				if(*(short *) tda_base_getdata(&binaryFraction, i)){
					exponent = -(i);
					break;
				}
			}
		}else{
			exponent = 0;
		}
	}else{ //si numero es mayor a 1
		exponent = tda_get_end(&wholeNum);
	}

	//balancear exponente y agregarlo a la lista de num Flotante
	balancedExponent = convertDecimalBinary(exponent + 127);
	for(int i = 0; i< EXPONENT; i++){
		short binaryDigit = *(short*) tda_base_getdata(&balancedExponent, i + 1);
		printf("%d\n", binaryDigit);
		tda_base_add_copy(&floating, (void *) &binaryDigit);
	}

	//unir parte entera con fracional en base del movimiento del exponente
	// if(exponent == 0){
		
	// }

	printf("exponent balanced is %d\n", exponent);


	//printf("wholeNum is %d\n", wholeNum);
	//printf("fraction is %f\n", fraction);

	//printf("wholeNum in binary %d\n", convertDecimalBinary(atoi(wholeNum)) );

	//liberar memoria
	tda_base_destroy(&binaryFraction);
	tda_base_destroy(&wholeNum);
	tda_base_destroy(&balancedExponent);

	return floating; //lista retornado debe ser destruido despues de ser usado
} 

unsigned long listToLong(tda_base_t** shortList, int listSize){
	unsigned long result = 0;

 	

	return result;
}	

//convierte los elementos de una lista con datos de tipo short a un str
void listToStr(tda_base_t * shortList, char *str, int listSize){
	for(int i = 0; i< listSize; i++)
		//obtiene la la referencia al dato y hace cast a char antes de guardar
		str[i] = *(int*)tda_base_getdata(&shortList, i + 1) + '0';
} 