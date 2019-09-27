//Questo maint_test.c DIVENTERÀ digioTest.c

#include <avr/io.h>
#include <util/delay.h>
#include "digio.h"
//Per ora utilizziamo quella del prof Grisetti
#include "uart.h"

//questa funzione restituisce il valore memorizzato nel registro 
void printMyStatus ()

int main(int argc, char *argv[])
{
//Richiamo le inizializzazioni dei PWM contenute in digio.c
	initDigio();	



//l'intensità è invera al valore messo sulla soglia della func ledDimmer. Si potrebbe modificare la lib digio.c (e relativo .h)
	ledDimmer(13, 2);
	/*while(1)
	{
	int i;
		for(i=3; i<13; i++)
		{
			ledOn(i);
			_delay_ms(500);
			ledOff(i);
			if(i==12)
			{i=2;}
		}
	}*/
	return 0;
}
