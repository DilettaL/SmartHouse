#include <stdio.h>
#include <util/delay.h>
#include "smarthouse_functions.h"
#include "digio.h"
int main()
{
	PDigital test;
	test->dir=Output;
while(1)
{
	test->value=1;
	Digital_Pin(test, DigitalTypeLed, 10);
	_delay_ms(2000);
	test->value=0;
	Digital_Pin(test, DigitalTypeLed, 10);	
	_delay_ms(2000);
}
	return 0;
}
