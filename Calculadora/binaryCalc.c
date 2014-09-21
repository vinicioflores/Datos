#include "binaryCalc.h"

/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un una francion decimal a binario */
static void convertDecimalBinary(tda_base_t ** wholeNumList);
/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un un entero decimal a binario */
static void convertDecimalBinary(tda_base_t ** floatingList);

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
	int base = 10, digit;;
	int lenList = tda_get_end(&*listDigits);

	for(int i = 1; i<= lenList; i++){
		//si el digito no es menor al divisor
		digit = *(int *) tda_base_getdata(&*listDigits, i);
		/* Si el numero a dividir es menor al divisor agregar
			bajar el proximo digito de la lista */
		if(digit< divisor){
			for(int j = 1;digit < divisor || i<= lenList; j++)
				digit = digit * pow(base, j) + *(int*)tda_base_getdata(&*listDigits, i++);
		}else{
			digit = digit / divisor;
		}

		tda_base_add_copy(&tempList, &digit);
	}

	tda_base_destroy(&*listDigits);
	*listDigits = tempList;
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

	tda_base_t *binary = NULL;

	//si decimal no es 0
	if(lenList > 1 && !*(int*)tda_base_getdata(&*wholeNumList, 1)){
		//hasta que sea 0
		for(;lenList > 1 && !*(int*)tda_base_getdata(&*wholeNumList, 1);){
			binaryDigit = *(int*)tda_base_getdata(&*wholeNumList, lenList) % 2;
			printf("Binary digit is: %d\n", binaryDigit);
			tda_base_add_copy(&binary, (void *) &binaryDigit);
			divideList(&*wholeNumList, 2);
		}
	}else{
		tda_base_add_copy(&binary, tda_base_getdata(&*wholeNumList, 1));
	}

	/*cambiar roden ya que algoritmo de multiplicar cambia de posicion los digitos
	mas y menos significativos del digito */
	tda_base_reverseElements(&binary);
	tda_base_destroy(&*wholeNumList);
	*wholeNumList = binary;
}

static void convertDecimalFractionBinary(tda_base_t ** floatingList){
	tda_base_t *binaryFraction = NULL;

	int bit0 = 0, bit1 = 1;
	int lenList = tda_get_end(&*floatingList);
	int newLenList;

	for(int i = 0; i < MANTISA; i++){
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

tda_base_t *convertBinaryDecimal(char sign, char wholeDeci[], char fraction[]){
	tda_base_t *floating = NULL;
	tda_base_t *wholeBinaryNum = NULL;
	tda_base_t *binaryFraction = NULL;

	//insertar los chars en listas y convertir a digitos
	strToListDigits(wholeDeci, &wholeBinaryNum);
	strToListDigits(fraction, &binaryFraction);

	/* Convert list of digits to binary */
	convertDecimalBinary(&wholeBinaryNum);





	int tempListSize = tda_get_end(&wholeBinaryNum);
	char tempString[10];
	listToStr(wholeBinaryNum, tempString, tempListSize);
	printf("Number is: %s\n", tempString);

	// multiplyList(&wholeBinaryNum, 2);
	// tempListSize = tda_get_end(&wholeBinaryNum);
	// listToStr(wholeBinaryNum, tempString, tempListSize);
	// printf("Multiplied Number is: %s\n", tempString);


	return floating;

	// tda_base_t *floating = NULL;
	// tda_base_t *binaryFraction = NULL;
	// tda_base_t *wholeBinaryNum = NULL;
	// tda_base_t *balancedExponent = NULL;

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

	// //convertir parte entero a binario
	// wholeDeci = (int) atoi(decimal + sign);
	// wholeBinaryNum = convertDecimalBinary(wholeDeci);
	// lengthWholeBinary = tda_get_end(&wholeBinaryNum);//cant elementos

	// //convertir parte fracionario a binario
	// fractionDeci = atof(decimal + sign) - (int) atoi(decimal + sign);
	// binaryFraction = convertDecimalFractionBinary(fractionDeci);
	// lengthBinaryFraction = tda_get_end(&binaryFraction); //cant elementos

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
		str[i - 1] = *(short*)tda_base_getdata(&shortList, i) + '0';
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