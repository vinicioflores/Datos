#include "binaryCalc.h"

/*retorna referencia a una lista que contiene en cada nodo un short
lo cual es el resultado de la conversion de un una francion decimal a binario */
static void convertDecimalBinary(tda_base_t ** wholeNumList);
///acepta un int normal y lo retorna en representacion binario en una lista
static tda_base_t * convertNaturalDecimalBinary(unsigned int decimal);

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
	int binaryDigit;
	int lenList = tda_get_end(&*wholeNumList);
	int wholeDigit = *(int*)tda_base_getdata(&*wholeNumList, 1);

	tda_base_t *binary = NULL;
	
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
		/*cambiar roden ya que algoritmo de multiplicar cambia de posicion los digitos
	mas y menos significativos del digito */
	tda_base_reverseElements(&binary);
	tda_base_destroy(&*wholeNumList);
	*wholeNumList = binary;
}

static int convertBinaryToDecimal(tda_base_t **decimalNum){
	int strLenth = tda_get_end(&*decimalNum);
	unsigned int wholeNum = 0;

	int digit;
	for(int i = 1; i<= strLenth; i++){
		digit = *(int*) tda_base_getdata(&*decimalNum, strLenth - i + 1);
		wholeNum += digit * pow(2, i-1);
	}

	return wholeNum;
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

	if(!(lenList == 1 && tda_base_getdata(&*floatingList, 1) == 0)){
		for(int i = 0; i < mantisa; i++){
			multiplyList(&*floatingList, 2);

			newLenList = tda_get_end(&*floatingList);

			if(newLenList > lenList){
				tda_base_delete(&*floatingList, 1);
				tda_base_add_copy(&binaryFraction, (void *) &bit1);
				newLenList--;
			}else{
				tda_base_add_copy(&binaryFraction, (void *) &bit0);
			}
		}//fin for
	}else{
		for(int i = 0; i < mantisa; i++){
			tda_base_add_copy(&binaryFraction, (void *) &bit0);
		}
	}

	tda_base_destroy(&*floatingList);
	*floatingList = binaryFraction;	
}

//valor lo retorna por referencia a "exponentFloat" y "mantissaFloat"
void convertDecimalFloating(char wholeDeci[], char fraction[],
 char **exponentFloat, char **mantissaFloat){
	tda_base_t *wholeBinaryNum = NULL;
	tda_base_t *binaryFraction = NULL;
	tda_base_t *balancedExponent = NULL;
	tda_base_t *mantissa = NULL;

	int mantisa = PRECISION - EXPO_SLOTS - 1;
	int listSize, exponentShift = 0;


	//insertar los chars en listas y convertir a digitos
	strToListDigits(wholeDeci, &wholeBinaryNum);
	strToListDigits(fraction, &binaryFraction);

	/* Convertir la lista de digitos (parte enterea) */
	convertDecimalBinary(&wholeBinaryNum);
	convertDecimalFractionBinary(&binaryFraction, mantisa);

	//longitud num's binarios
	int lengthWholeBinary = tda_get_end(&wholeBinaryNum);
	int lengthBinaryFraction = tda_get_end(&binaryFraction);

	printf("Exponente campo es %d y mantisa es %d\n", EXPO_SLOTS, mantisa);
	

    //encontrar digito antes del punto
	int index = lengthWholeBinary;
	if(index <= 1){
		int keyDigit;

		if(index != 0)
			keyDigit = 1;
		else
			keyDigit = 0;

		if(keyDigit == 0){//si digito es insinificativo
			for(int i = 1; i <= lengthBinaryFraction; i++){
				/*cantidad de veces correr punto decimal a la izquierda
				para cuando es 0 */
				if(*(int *) tda_base_getdata(&binaryFraction, i)){
					exponentShift= -(i);
					break;
				}
			}
		}else{
			exponentShift = 0;
		}
	}else{ 
		exponentShift = lengthWholeBinary - 1;
	}

	printf("Exponent shift is: %d\n", exponentShift);
	
	int decimalBalancedExponent = exponentShift + pow(2, EXPO_SLOTS - 1) - 1;
	printf("Complement is : %d\n", decimalBalancedExponent);

	//arreglo de indice si exponente es 0
	if(exponentShift == 0)
		exponentShift = 1;

	//balancear exponente y agregarlo a la lista de num Flotante
	balancedExponent = convertNaturalDecimalBinary(decimalBalancedExponent);

	//agregar 0's insignificativos al exponentBalanceado
	int balancedExponentLength = tda_get_end(&balancedExponent);
	int bit0 = 0;
	if(balancedExponentLength < EXPO_SLOTS){
		tda_base_reverseElements(&balancedExponent);
		while(balancedExponentLength < EXPO_SLOTS){
			tda_base_add_copy(&balancedExponent, (void *)&bit0);
			balancedExponentLength = tda_get_end(&balancedExponent);
		}
		tda_base_reverseElements(&balancedExponent);
	}//fin 0's insignificativos

	 /*si la parte entera contiene mas de un digito,
	 exponent es cantidad de digitos en wholeBinaryNum */ 
	int start;
	if(exponentShift >= 1){
		//copiar los digitos binario del entero a la lista floante quitar primer 1
		for(int i = 2; i <= index; i++){
			int binaryDigit = *(int*) tda_base_getdata(&wholeBinaryNum, i);
			tda_base_add_copy(&mantissa, (void *) &binaryDigit);
		}
		start = 1;
	}else{ //si entero es 0
		start = -exponentShift - 1;
	}
	printf("Index is %d\n", index);
	//agregar parte fracionaria
	for(; start <= lengthBinaryFraction - index; start++){
		int binaryDigit = *(int*) tda_base_getdata(&binaryFraction, start);
		tda_base_add_copy(&mantissa, (void *) &binaryDigit);
	}

	//liberar memoria
	tda_base_destroy(&wholeBinaryNum);
	tda_base_destroy(&binaryFraction);

	//Retorna el exponent binario balanceado y la mantissa flotante
	listSize = tda_get_end(&balancedExponent);
	*exponentFloat = malloc(sizeof(char)* listSize * tda_get_end(&mantissa));
    listToStr(balancedExponent, *exponentFloat, listSize);

	listSize = tda_get_end(&mantissa);
	*mantissaFloat = malloc(sizeof(char)* listSize);
    listToStr(mantissa, *mantissaFloat, listSize);
} 

//valor en decimal lo retorna por referencia es "wholenumber" y "fraction"
float convertFloatToDeci(char exponent[], char mantissa[]){
	tda_base_t *decimalNum = NULL;
	tda_base_t *exponentNum = NULL;

	strToListDigits(mantissa, &decimalNum);
	strToListDigits(exponent, &exponentNum);

	int mantissaDecimal = convertBinaryToDecimal(&decimalNum);
	int unbalancedExponent = convertBinaryToDecimal(&exponentNum);

	float result = 0.0f;
	int shift = unbalancedExponent - pow(2, EXPO_SLOTS - 1) + 1;
	result = (mantissaDecimal / pow(2, strlen(mantissa)) + 1) * pow(2,shift);
    
	//printf("mantissa is: %d and exponent is: %d\n", mantissaDecimal, unbalancedExponent);
	//printf("result is %f\n", result);
	return result;

}

//convierte los elementos de una lista con datos de tipo short a un str
void listToStr(tda_base_t * shortList, char *str, int listSize){
	for(int i = 1; i <= listSize; i++){
		//obtiene la la referencia al dato y hace cast a char antes de guardar
		str[i - 1] = *(int*)tda_base_getdata(&shortList, i) + '0';
	}
} 