#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "digio.h"
#include "pins.h"
#include "uart.h"
/*TEST*/
#include <avr/interrupt.h>

void ledOn(uint8_t pin)
{
	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register) |= mask;
	*(mapping->out_register) |= mask;
}

void ledOff(uint8_t pin)
{
	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register) |= mask;
	*(mapping->out_register) &=~ mask;
}

void ledDimmer(uint8_t pin, uint8_t intensity)
{
/*TEST*/printf_init();
	//PWM_init
	//TCCR0A=(1<<WGM00)|(1<<WGM01);
 	//TCCR0B=(1<<CS00);
	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register) |= mask;
	//PWM_enable
		//Settare tutti i timer e i parametri della struct da utilizzare nel caso in cui richieste info
	//PWM_setOutput
	//PWM_dutyCycle
	while(1)
	{
/*TEST*/	printf("v %u\n", (int) OCR1CL);
	}

/*	uint8_t light=0;
	*(mapping->oc_register_high)=0;
TCCRA=*(mapping->com_mask);
	while(1)
	{
		*(mapping->oc_register_low)=light;
		light+=8;
		_delay_ms(100);
	}
*/
}

void digitalInput(uint8_t pin)
{
	// this initializes the printf/uart thingies
	printf_init(); 
	const Pin* mapping=pins+pin;
	uint8_t result; //inizializzo il valore di lettura qua in modo da non definirlo ogni volta
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register) |=mask; //dovrebbe essere equivalente a &=~
	*(mapping->out_register) |=mask; //in questo caso si attiva il resistore di pull up essendo il pin un ingresso	
	while(1)
	{
		_delay_ms(1000);
/*Potrebbe non funzionarci perché sono necessarie delle nop per effettuare la sincronizzazione, io per ora ho messo il delay prima*/
		int key=(*(mapping->in_register) & mask)==0;
/*dato che il risultato viene messo direttamente in in_register non ho capito perché ha inserito key e le altre cose*/
		printf("switch: %d\n", key);
	}
}

