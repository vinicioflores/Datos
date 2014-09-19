#include "binaryCalc.h"

/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un una francion decimal a binario */
static tda_base_t *convertDecimalFractionBinary(float deciFraction);
/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un un entero decimal a binario */
static tda_base_t *convertDecimalBinary(unsigned int decimal);

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
	tda_base_t *wholeBinaryNum = NULL;
	tda_base_t *balancedExponent = NULL;

	short binaryDigit; //digito para guardar bit temporal
	int index = 0, lengthWholeBinary, lengthBinaryFraction;
	int wholeDeci; //parte entero
	float fractionDeci; //parte fracionaria
	unsigned int exponent = 0;

	short sign = 0; //sign
	if(decimal[index] == '-') //si es un numero negativo
			sign = 1;
	//agregar signo axponente a lista
	tda_base_add_copy(&floating, (void *) &sign);

	//convertir parte entero a binario
	wholeDeci = (int) atoi(decimal + sign);
	wholeBinaryNum = convertDecimalBinary(wholeDeci);
	lengthWholeBinary = tda_get_end(&wholeBinaryNum);//cant elementos

	//convertir parte fracionario a binario
	fractionDeci = atof(decimal + sign) - (int) atoi(decimal + sign);
	binaryFraction = convertDecimalFractionBinary(fractionDeci);
	lengthBinaryFraction = tda_get_end(&binaryFraction); //cant elementos

	//encontrar digito antes del punto
	index = lengthWholeBinary;
	if(index == 1){//si parte entera solo tiene un digito
		short keyDigit = *(short*) tda_base_getdata(&wholeBinaryNum, index);

		if(keyDigit == 0){//si numero es menor a 1
			for(int i = 1; i <= lengthBinaryFraction; i++){
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
		exponent = lengthWholeBinary;
	}

	//balancear exponente y agregarlo a la lista de num Flotante
	balancedExponent = convertDecimalBinary(exponent + 127);
	//printf("amount elements: %d\n", tda_get_end(&balancedExponent));
	tda_base_reverseElements(&balancedExponent);
	//printf("amount elements: %d\n", tda_get_end(&balancedExponent));
	for(int i = 1; i<= EXPONENT; i++){
		binaryDigit = *(short*) tda_base_getdata(&balancedExponent, i);
		tda_base_add_copy(&floating, (void *) &binaryDigit);
	}

	printf("exponent balanced is %d\n", exponent);

	//si la parte entera contiene mas de un digito, index es cantidad de digitos en wholeBinaryNum
	if(balancedExponent - 127 >= 0){
		//copiar los digitos binario del entero a la lista floante quitar primer 1
		for(int i = 2; i <= index; i++){
			binaryDigit = *(short*) tda_base_getdata(&wholeBinaryNum, i);
			tda_base_add_copy(&floating, (void *) &binaryDigit);
		}
	}	

	int start = 1;
	if(exponent < 127)
		start = 127 - exponent;
	for(; start <= lengthBinaryFraction; start++){
		binaryDigit = *(short*) tda_base_getdata(&binaryFraction, start);
		tda_base_add_copy(&floating, (void *) &binaryDigit);
	}


	//printf("wholeBinaryNum is %d\n", wholeBinaryNum);
	//printf("fraction is %f\n", fraction);
	//printf("wholeBinaryNum in binary %d\n", convertDecimalBinary(atoi(wholeBinaryNum)) );

	//liberar memoria
	tda_base_destroy(&binaryFraction);
	tda_base_destroy(&wholeBinaryNum);
	tda_base_destroy(&balancedExponent);

	return floating; //lista retornado debe ser destruido despues de ser usado
} 

//convierte los elementos de una lista con datos de tipo short a un str
void listToStr(tda_base_t * shortList, char *str, int listSize){
	for(int i = 1; i <= listSize; i++){
		//obtiene la la referencia al dato y hace cast a char antes de guardar
		str[i - 1] = (*(short*)tda_base_getdata(&shortList, i)) + '0';
	}
} 

//muestra el numero flotante en forma binario
void printFloa(tda_base_t * floating){
	int listSize = tda_get_end(&floating);
	char *floatingStr = malloc(sizeof(char) * listSize);
	listToStr(floating, floatingStr, listSize);
	puts("\nNumero Floatante en bits es: \n");
	printf("Signo: %c\n", floatingStr[0]);

	printf("Exponente:");
	int i;
	for(i = 1; i <= EXPONENT; i++)
		printf("%c", floatingStr[i]);
	puts("");

	printf("Mantissa: %s\n", floatingStr + i + 1);
	free(floatingStr);
}