#include <avr/io.h>
#include "adc.h"
#include <util/delay.h>
//uart.h Grisetti
#include "uart.h"
/*Per correttezza questi test andrebbero riscritti facendo in modo di poter leggere su UART i valori attesi senza necessità di dover collegare led ?? */
int main(int argc, char *argv[])
{
	adc_init();
	//Scelgo il pin 0 con 10 campioni
	adc_run(0, 0);
	return 0;
}
