//Standard Libraries
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>//per open
#include <fcntl.h>
#include <unistd.h> //per read in listen_serial
//Low Level Libraries
//#include "eeprom.h"
//#include "adc.h"
//#include "digio.h"
//High Level Libraries
#include "smarthouse_comm.h"
#include "smarthouse_shell_globals.h"

void *listen_keyboard()
{
	char ch;
	ch=getchar();
	if(ch < 0)
	{
   		if (ferror(stdin))
		{
              		clearerr(stdin);
		}	        
	}
	//flushInputBuffer
}

void *listen_serial()
{
int operazione_completata=1;
	//Condizione per l'utilizzo della seriale - magari per l'abilitazione dell'interrupt
	if(operazione_completata)
	{
		printf("Seriale\n");
		int serial=open ("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC );
  		if (serial < 0)
		{
    			printf ("error opening serial, serial %d\n", serial);
  		}
		char c;
//		while(c!=EOT)
//		{
			read(serial, &c, 1);
			printf("letto %02x\n", (unsigned int)c);
//		}
	}
}

int main (int argc, char argv[])
{
	//Inizializzazione funzioni basso livello
//	adc_init();
//	digio_init();
	//Inizializzazione funzioni alto livello //uart_init la inizializzo in Smarthouse_comm_init()
//	Smarthouse_comm_init();
	//Threads creations
	pthread_t keyboard, serial;
	pthread_attr_t attr_keyboard, attr_serial;
	pthread_attr_init(&attr_keyboard);
	pthread_attr_init(&attr_serial);
	int control1=pthread_create(&keyboard, &attr_keyboard, listen_keyboard, NULL);
	int control2=pthread_create(&serial, &attr_serial, listen_serial, NULL);
	if (control1 || control2)
	{
         	printf("ERROR; return code from pthread_create()\n");
         	exit(-1);
      	}
	int run=1;
/*A questo punto si ha un while con while(run), che tanto l'istruzione quit fa un run=0 return 0
	while(run)
	{
*/		printf("$>Smarthouse:");
		//Apertura shell iniziale per inserire il comando	
		while(	pthread_join(keyboard, NULL)!=0 || pthread_join(serial, NULL)!=0 );
//	}
	pthread_attr_destroy(&attr_keyboard);
  	pthread_attr_destroy(&attr_serial);	
	return 0;
}
