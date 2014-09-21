#include "testBinaryCalc.h"

void testConversion(void){
	int result = 0;
	//result = convertDecimalBinary(10) == 1010 && convertDecimalBinary(33) == 100001;
	
	if(result)
		puts("OK!");
	else
		puts("Deci to Binary FAIL");
}

void testDeciToFloating(void){
	tda_base_t *floatingNum;

	floatingNum = convertBinaryDecimal("2.5");
	printFloa(floatingNum);
	tda_base_destroy(&floatingNum);
	
	puts("OK!");
}
