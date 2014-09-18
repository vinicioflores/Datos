#include "testBinaryCalc.h"

void testConversion(void){
	int result;
	result = convertDecimalBinary(10) == 1010 && convertDecimalBinary(33) == 100001;
	
	if(result)
		puts("OK!");
	else
		puts("Deci to Binary FAIL");
}

void testDeciToFloating(void){
	tda_base_t *floatingNum;

	floatingNum = convertBinaryDecimal("0.15625");

	tda_base_destroy(&floatingNum);
	
	puts("OK!");
}
