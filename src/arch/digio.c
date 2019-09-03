#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "digio.h"
#include "pins.h"
#include "../include/uart.h"

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
	uint8_t light=0;
	const Pin* mapping=pins+pin;
	*(mapping->oc_register_high)=0;
//TCCRA=*(mapping->com_mask);
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register) |= mask;
	while(1)
	{
		*(mapping->oc_register_low)=light;
		light+=8;
		_delay_ms(100);
	}
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
		result= *(mapping->in_register);
/*dato che il risultato viene messo direttamente in in_register non ho capito perché ha inserito key e le altre cose*/
		printf("switch: %d\n", result);
	}
/*
****************************************************
//UTILIZZARE SOLO PIN CHE UNANO PIN CHANGE!!

  // this initializes the printf/uart thingies
	printf_init(); 

	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register)&=~ mask;
	*(mapping->out_register)|= mask;
	while(1)
	{
		//uint8_t result= *(mapping->in_register);		
//		int key=(PINB&mask)==0; // we extract the bit value of the 6th bit
		//printf("switch %02x, %d\n", (int) PORTB, key);
		//_delay_ms(500); // from delay.h, wait 1 sec
	}
****************************************************
*/
}

