#include <avr/io.h>
#include "adc.h"
#include <util/delay.h>
//uart.h Grisetti
#include "uart_ORIGINAL.h"
#include "digio.h"
/*Per correttezza questi test andrebbero riscritti facendo in modo di poter leggere su UART i valori attesi senza necessità di dover collegare led ?? */
int main(int argc, char *argv[])
{
	digio_init();
	printf_init();
	ledDimmer(13,80);
	adc_init();
//Inserire pin per pwm
	//Scelgo il pin 0 con 10 campioni
	while (1){
	adc_run(0, 10);
	}
	return 0;
}
