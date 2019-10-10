//Standard Libraries
#include <stdio.h>
#include <pthread.h>
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
	//Threads creations
	pthread_t keyboard, serial;
	pthread_attr_t attr_keyboard, attr_serial;
	pthread_attr_init(&attr_keyboard);
	pthread_attr_init(&attr_serial);
	phtread_create(&keyboard, &attr_keyboard, listen_keyboard, NULL); 
	serial_resultphtread_create(&serial, &attr_serial, listen_serial, NULL); 
	void *keyboard_result, *serial_result;

	while(exit)
	{	
		while( (pthread_join(keyboard, &keyboard_result)!=0) || (pthread_join(serial, &serial_result)!=0) )
		{
			//Orazio Shell	
//			Smarthouse_shellStart()
		}
	}
	pthread_attr_destroy(&attr_keyboard);
  	pthread_attr_destroy(&attr_serial);
	return 0;
}
