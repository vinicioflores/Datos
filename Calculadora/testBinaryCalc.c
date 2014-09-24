#include "testBinaryCalc.h"

void testDeciToFloating(void){
	int precision = 32;
	char sign = '-';
	char whole[] = "0";
	char fraction[] = "84";

	char *exponentFloat = NULL;
	char *mantissaFloat = NULL;
	convertBinaryDecimal(whole, fraction, precision, 
		&exponentFloat, &mantissaFloat);

	//exponente
	printf("%s\n", exponentFloat);
	//mantissa
	printf("%s\n", mantissaFloat);

	free(exponentFloat);
	free(mantissaFloat);
	
	puts("OK!");
}
