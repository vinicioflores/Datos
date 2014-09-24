#include "binaryCalc.h"

/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un una francion decimal a binario */
static void convertDecimalBinary(tda_base_t ** wholeNumList);
/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un un entero decimal a binario */
static void convertDecimalBinary(tda_base_t ** floatingList);
//acepta un int normal y lo retorna en representacion binario en una lista
static tda_base_t * convertNaturalDecimalBinary(unsigned int decimal);

//numero digitos en un numero
int nlen(unsigned int digit){
	for(int i = 1;;i++){
		if(digit < pow(10, i)){
			return i;
		}
	}
}

static void strToListDigits(char charInts[], tda_base_t ** listInts){
	for(int i = 0; i < strlen(charInts); i++){
		int tempDigit = charInts[i] - '0';
		tda_base_add_copy(&*listInts, (void *) &tempDigit);
	}
}

/* Divide una lista de enteros base 10 entre un divisor menor a 10 */
static void divideList(tda_base_t ** listDigits, int divisor){
	tda_base_t *tempList = NULL;
	int base = 10;
	int digit;
	int carry = 0, significativo = 0;
	int lenList = tda_get_end(&*listDigits);

	for(int i = 1; i<= lenList; i++){
		//si el digito no es menor al divisor
		digit = *(int *) tda_base_getdata(&*listDigits, i);

		//arreglar digito agregandolo el carry (si hay uno)
		digit += carry;
		carry = 0;

		//calcular el carry si hay uno
		carry = (digit % divisor) * base;
		//hacer la division
		digit = digit / divisor;

		if(digit)
			significativo = 1; //si ya no hay ceros insignificativos
		
		//si no es es un 0 insignificativo
		if(significativo)
			tda_base_add_copy(&tempList, &digit);
	}

	tda_base_destroy(&*listDigits);
	*listDigits = tempList;

	// char result[20];
	// listToStr(tempList, result, tda_get_end(&tempList));
	// printf("Divided number is now: %s\n", result);
}

/* Multiplica una lista de digitos (ints) en base 10 */
static void multiplyList(tda_base_t ** listDigits, int multiplier){
	tda_base_t *tempList = NULL;
	int base = 10; //base en el cual se trabaja la multiplicacion
	int lenList = tda_get_end(&*listDigits);
	int carry = 0, tempDigit;;
	
	//dar vuelta a la lista para facimente multiplicar de derecha a izquierda
	tda_base_reverseElements(&*listDigits);
	//multiplicar cada digito y llevar carry si es necesario
	int i;
	for(i = 1; i <= lenList; i++){
		tempDigit = *(int *) tda_base_getdata(&*listDigits, i);
		tempDigit = (tempDigit * multiplier) + carry;
		carry = 0;

		//llevar un carry si el digito es muy grande
		if(tempDigit > (base - 1))
			carry = tempDigit / base;
			//agregar el carry
		
		tempDigit = tempDigit % base;
		tda_base_add_copy(&tempList, &tempDigit);
	}

	//si hay un ultimo carry por agregar
	if(carry > 0){
		tda_base_add_copy(&tempList, &carry);
		i++;
	}
	//agregar los 0's significativos
	for(; i <= lenList; i++){
		tempDigit = 0;
		tda_base_add_copy(&tempList, &tempDigit);
	}

	tda_base_reverseElements(&tempList);
	tda_base_destroy(&*listDigits);
	*listDigits = tempList;
}

//cambia la lista con digitos enteros base 10 por uno base 2.
static void convertDecimalBinary(tda_base_t ** wholeNumList){
	short binaryDigit;
	int lenList = tda_get_end(&*wholeNumList);
	int wholeDigit = *(int*)tda_base_getdata(&*wholeNumList, 1);

	tda_base_t *binary = NULL;

	if(wholeDigit != 0 && lenList == 1){
		tda_base_add_copy(&binary, tda_base_getdata(&*wholeNumList, 1));
	}else{
		//hasta que sea 0 el numero decimal
		while(lenList > 1 || *(int*)tda_base_getdata(&*wholeNumList, 1) != 0){
			//obtener digito binario con modulo
			wholeDigit = *(int*)tda_base_getdata(&*wholeNumList, lenList);
			binaryDigit = wholeDigit % 2;
	
			tda_base_add_copy(&binary, (void *) &binaryDigit);

			divideList(&*wholeNumList, 2);
	
			lenList = tda_get_end(&*wholeNumList);

			if(lenList == 0)
				break;
		}
	}

	/*cambiar roden ya que algoritmo de multiplicar cambia de posicion los digitos
	mas y menos significativos del digito */
	tda_base_reverseElements(&binary);
	tda_base_destroy(&*wholeNumList);
	*wholeNumList = binary;
}

static tda_base_t * convertNaturalDecimalBinary(unsigned int decimal){
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
		
		/*cambiar roden ya que algoritmo de multiplicar cambia de posicion los digitos
		 mas y menos significativos del digito */
		tda_base_reverseElements(&binary);
		return binary;
}

static void convertDecimalFractionBinary(tda_base_t ** floatingList, int mantisa){
	tda_base_t *binaryFraction = NULL;

	int bit0 = 0, bit1 = 1;
	int lenList = tda_get_end(&*floatingList);
	int newLenList;

	for(int i = 0; i < mantisa; i++){
		multiplyList(&*floatingList, 2);

		newLenList = tda_get_end(&*floatingList);

		if(newLenList > lenList){
			tda_base_delete(&*floatingList, 1);
			tda_base_add_copy(&binaryFraction, (void *) &bit1);
		}else{
			tda_base_add_copy(&binaryFraction, (void *) &bit0);
		}
	}//fin for

	tda_base_destroy(&*floatingList);
	*floatingList = binaryFraction;
}

void convertBinaryDecimal(char *sign, char wholeDeci[], char fraction[], int presicion){
	tda_base_t *wholeBinaryNum = NULL;
	tda_base_t *binaryFraction = NULL;
	tda_base_t *balancedExponent = NULL;
	tda_base_t *mantissa = NULL;

	int exponentSlots = (presicion / 32) + 7; //cantidad digito exponente
	int mantisa = presicion - exponentSlots - 1;
	int listSize;

	printf("Exponente campo es %d y mantisa es %d\n", exponentSlots, mantisa);

	//insertar los chars en listas y convertir a digitos
	strToListDigits(wholeDeci, &wholeBinaryNum);
	strToListDigits(fraction, &binaryFraction);

	/* Convertir la lista de digitos a su represnetacion binario */
	convertDecimalBinary(&wholeBinaryNum);
	convertDecimalFractionBinary(&binaryFraction, mantisa);

	int lengthWholeBinary = tda_get_end(&wholeBinaryNum);
	int lengthBinaryFraction = tda_get_end(&binaryFraction);

    //encontrar digito antes del punto
	int index = lengthWholeBinary, exponentShift;
	if(index == 1){//si parte entera solo tiene un digito
		int keyDigit = *(int*) tda_base_getdata(&wholeBinaryNum, index);

		if(keyDigit == 0){//si numero es menor a 1
			for(int i = 1; i <= lengthBinaryFraction; i++){
				//cantidad de veces correr punto decimal a la izquierda
				if(!*(int *) tda_base_getdata(&binaryFraction, i)){
					exponentShift = -(i);
					break;
				}
			}
		}else{
			exponentShift = 0;
		}
	}else{ //si numero es mayor a 1
		exponentShift = lengthWholeBinary - 1;
	}

	//balancear exponente y agregarlo a la lista de num Flotante
	balancedExponent = convertNaturalDecimalBinary(exponentShift
	 + pow(2, exponentSlots -1) - 1);

	/* si la parte entera contiene mas de un digito,
	 exponent es cantidad de digitos en wholeBinaryNum */
	if(exponentShift >= 1){
		//copiar los digitos binario del entero a la lista floante quitar primer 1
		for(int i = 1; i <= index; i++){
			int binaryDigit = *(int*) tda_base_getdata(&wholeBinaryNum, i);
			tda_base_add_copy(&mantissa, (void *) &binaryDigit);
		}
	}
	
	listSize = tda_get_end(&balancedExponent);
	char *exponentBalancedStr = malloc(sizeof(char)* listSize);
    listToStr(balancedExponent, exponentBalancedStr, listSize);

	printf("Exponent is: %s\n", exponentBalancedStr);

	//agregar parte fracionaria
	for(int start = 1; start <= lengthBinaryFraction; start++){
		int binaryDigit = *(int*) tda_base_getdata(&binaryFraction, start);
		tda_base_add_copy(&mantissa, (void *) &binaryDigit);
	}

	listSize = tda_get_end(&mantissa);
	char *mantisaStr = malloc(sizeof(char)* listSize);
    listToStr(mantissa, mantisaStr, listSize);

	printf("Mantissa is: %s\n", mantisaStr);

	free(mantisaStr);
	free(exponentBalancedStr);




	// short binaryDigit; //digito para guardar bit temporal
	// int index = 0, lengthWholeBinary, lengthBinaryFraction;
	// int wholeDeci; //parte entero
	// float fractionDeci; //parte fracionaria
	// unsigned int exponent = 0;

	// short sign = 0; //sign
	// if(decimal[index] == '-') //si es un numero negativo
	// 		sign = 1;
	// //agregar signo axponente a lista
	// tda_base_add_copy(&floating, (void *) &sign);




	// //encontrar digito antes del punto
	// index = lengthWholeBinary;
	// printf("lengthWholeBinary is: %d \n", index);
	// if(index == 1){//si parte entera solo tiene un digito
	// 	short keyDigit = *(short*) tda_base_getdata(&wholeBinaryNum, index);

	// 	if(keyDigit == 0){//si numero es menor a 1
	// 		for(int i = 1; i <= lengthBinaryFraction; i++){
	// 			//cantidad de veces correr punto decimal a la izquierda
	// 			if(!*(short *) tda_base_getdata(&binaryFraction, i)){
	// 				exponent = -(i);
	// 				break;
	// 			}
	// 		}
	// 	}else{
	// 		exponent = 0;
	// 	}
	// }else{ //si numero es mayor a 1
	// 	exponent = lengthWholeBinary - 1;
	// }

	// //balancear exponente y agregarlo a la lista de num Flotante
	// balancedExponent = convertDecimalBinary(exponent + 127);
	// for(int i = 1; i<= EXPONENT; i++){
	// 	binaryDigit = *(short*) tda_base_getdata(&balancedExponent, i);
	// 	tda_base_add_copy(&floating, (void *) &binaryDigit);
	// }

	// printf("exponent balanced is %d\n", exponent);

	// /*si la parte entera contiene mas de un digito,
	//  exponent es cantidad de digitos en wholeBinaryNum */
	// if(exponent >= 1){
	// 	//copiar los digitos binario del entero a la lista floante quitar primer 1
	// 	for(int i = 1; i <= index; i++){
	// 		binaryDigit = *(short*) tda_base_getdata(&wholeBinaryNum, i);
	// 		tda_base_add_copy(&floating, (void *) &binaryDigit);
	// 	}
	// }	

	// for(int start = 1; start <= lengthBinaryFraction; start++){
	// 	binaryDigit = *(short*) tda_base_getdata(&binaryFraction, start);
	// 	tda_base_add_copy(&floating, (void *) &binaryDigit);
	// }

	// //liberar memoria
	// tda_base_destroy(&binaryFraction);
	// tda_base_destroy(&wholeBinaryNum);
	// tda_base_destroy(&balancedExponent);

	// return floating; //lista retornado debe ser destruido despues de ser usado
} 

//convierte los elementos de una lista con datos de tipo short a un str
void listToStr(tda_base_t * shortList, char *str, int listSize){
	for(int i = 1; i <= listSize; i++){
		//obtiene la la referencia al dato y hace cast a char antes de guardar
		str[i - 1] = *(int*)tda_base_getdata(&shortList, i) + '0';
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

	printf("Mantissa: %s\n", (floatingStr + i + 1));
	free(floatingStr);
}