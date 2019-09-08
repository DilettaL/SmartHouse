#include <avr/io.h>
#include "digio.h"
#include <util/delay.h>
//uart.h Grisetti
#include "uart.h"
/*Per correttezza questi test andrebbero riscritti facendo in modo di poter leggere su UART i valori attesi senza necessità di dover collegare led ?? */
int main(int argc, char *argv[])
{
	printf_init();
	while (1){
//accende e spegne i led digitali dal 2 al 13
		for(int i=2; i<14; i++)
		{
			ledOn(i);
			_delay_ms(500);
			ledOff(i);
			_delay_ms(500);
		}
	printf ("devo stampare il valore dei registri immagino... non le var i.. sbalgio??\n");
	}
/*		for(int i=2; i<14; i++)
		{
			ledOn(i);
			_delay_ms(500);
			ledOff(i);
			_delay_ms(500);
		}
	}
*/

//Test ledDimmer
	initDimmer();
	ledDimmer(13, 10);
//Test Digital In
/*
	while(1){
		digitalInput(12);
		_delay_ms(1000);
	}
*/
	return 0;
}
