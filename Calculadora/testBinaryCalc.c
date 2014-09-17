#include "testBinaryCalc.h"

void testConversion(void){
	int result;
	result = convertDecimalBinary(10) == 1010 && convertDecimalBinary(33) == 001001;
	
	if(result)
		puts("OK!");
	else
		puts("Deci to Binary FAIL");
}
