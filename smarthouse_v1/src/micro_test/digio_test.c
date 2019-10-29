#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "digio.h"
#include "uart_ORIGINAL.h"

#define NUM_DIGITAL_PINS 14

//Testa le funzionalità di digio.c
//Per il momento usa la uart del Prof. Grisetti "uart_ORIGINAL". Si può pensare ad un test v.2 che usa la nostra uart prendendo una struct in ingresso

uint8_t status_DDR [NUM_DIGITAL_PINS];
uint8_t status_PORT [NUM_DIGITAL_PINS];
uint8_t status_PIN [NUM_DIGITAL_PINS]; 

void myRegisterStatus (void){
//Creo 2 array, uno relativo al registro DDR, l'altro al registro PORT. Ogni bit dell'array corrisonde al valore che è stato settato per il relativo pin
	
	for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
		status_DDR [i] = getDDR(i);
		status_PORT [i] = getPORT(i);
		status_PIN [i] = getPIN(i);
	}
	printf ("DDR:\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\t13\n");
	for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
		printf ("\t%d", getDDR(i));
	}
	printf ("\n****************\n");

	printf ("PORT:\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\t13\n");
	for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
		printf ("\t%d", getPORT(i));
	}
	printf ("\n****************\n");

	printf ("PIN:\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\t13\n");
	for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
		printf ("\t%d", getPIN(i));
	}
	printf ("\n****************\n");
}

int main(int argc, char *argv[])
{
	digio_init();
	printf_init();
	uint8_t intensity = 0;

	while (1){
		printf ("\nFUNC: ledOff()\n");
		for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
			ledOff(i);
		}
		myRegisterStatus();
		_delay_ms (2000);
		
		printf ("\nFUNC: ledOn()\n");
		for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
			ledOn(i);
		}
		myRegisterStatus();
		_delay_ms (2000);

		printf ("\nFUNC: digitalInput()\n");
		printf ("*******VALORE LETTO PER OGNI PIN*********\n");
		printf ("N.Pin \t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\t13\n");
		for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
			digitalInput(i);
			printf ("\t%d", digitalInput(i));
		}
		printf ("\n\n");
		myRegisterStatus();
		_delay_ms (2000);

		printf ("\nFUNC: ledDimmer() - intensity %d\n", intensity);
		for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
				ledDimmer(i, intensity);
			}
		intensity = (intensity + 10) % 255;
		myRegisterStatus();
		_delay_ms (2000);
	}
	return 0;
}
