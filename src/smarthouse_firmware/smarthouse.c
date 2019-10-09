//Standard Libraries
#include <stdio.h>
//Low Level Libraries
#include "eeprom.h"
#include "adc.h"
#include "digio.h"
//High Level Libraries
#include "smarthouse_comm.h"
#include "smarthouse_shell_globals.h"

int exit=1;

int main (int argc, char argv[])
{
	//Inizializzazione funzioni basso livello
	adc_init();
	digio_init();
	//Inizializzazione funzioni alto livello //uart_init la inizializzo in Smarthouse_comm_init()
	Smarthouse_comm_init();
	while(exit)
	{	
		//Orazio Shell	
		Smarthouse_shellStart();
	}
	return 0;
}
