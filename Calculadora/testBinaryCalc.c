#include "testBinaryCalc.h"

void testDeciToFloating(void){
	char whole[] = "15";
	char fraction[] = "4";

	char *exponentFloat = NULL;
	char *mantissaFloat = NULL;
	convertDecimalFloating(whole, fraction, 
		&exponentFloat, &mantissaFloat);

	//exponente
	printf("%s\n", exponentFloat);
	//mantissa
	printf("%s\n", mantissaFloat);

	free(exponentFloat);
	free(mantissaFloat);
	
	puts("OK!");
}

void testFloatToDeci(void){
	char exponent[] = "01111111";
	char mantissa[] = "001010";

	float result = convertFloatToDeci(exponent, mantissa);

	printf("floating is now: %f\n", result);

	puts("OK");
}
