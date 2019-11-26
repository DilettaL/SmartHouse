#include "digio.h"
#include "uart.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>
//#include "pins.h"


int main(void) {
	// all pins as inputs with pull up resistors
	DigIO_init();

DigIO_setDirection(10, 1);
DigIO_setValue(10, 0);
	return 0;
}
