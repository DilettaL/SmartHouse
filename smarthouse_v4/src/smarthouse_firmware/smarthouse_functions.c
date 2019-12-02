#include "smarthouse_functions.h"
#include "digio.h"

//digital functions
void LedOn(uint8_t pin)
{
	DigIO_setDirection(pin, Output);
	DigIO_setValue(pin, 1);
}

void Smarthouse_digital(void)
{
	LedOn(10);
}
