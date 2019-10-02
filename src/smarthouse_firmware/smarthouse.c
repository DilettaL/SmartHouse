#include <stdio.h>
#include "eeprom.h"
#include "adc.h"
#include "digio.h"
#include "smarthouse_comm.h"

int main (int argc, char argv[])
{
	//Inizializzazione funzioni basso livello
	adc_init();
	//da rinominare cosìdigio_init();
	//da creare eeprom_init();
	//uart_init la inizializzo in Smarthouse_comm_init()
	//Inizializzazione funzioni alto livello
	Smarthouse_comm_init();
	while(1)
	{

	}
}
