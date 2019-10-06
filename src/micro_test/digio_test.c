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

void myRegisterStatus (void){
//Creo 2 array, uno relativo al registro DDR, l'altro al registro PORT. Ogni bit dell'array corrisonde al valore che è stato settato per il relativo pin
	
	for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
		status_DDR [i] = getDDR(i);
		status_PORT [i] = getPORT(i);
	}
}

int main(int argc, char *argv[])
{
	digio_init();
	printf_init();
	printf ("DDRx:\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12\t13\n");

	for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
		status_DDR [i] = getDDR(i);
		status_PORT [i] = getPORT(i);
	}
	while (1){
	for (int i = 0; i < NUM_DIGITAL_PINS; ++i){
		uint8_t regDDR = getDDR(1);
		printf ("\t%d", regDDR);
	}
	printf ("\n");
//		uint8_t regDDR = getDDR(1);
//		printf ("\t%d\n", regDDR);
		_delay_ms (2000);
	}
	return 0;
}
