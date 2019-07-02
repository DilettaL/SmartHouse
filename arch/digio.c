#include <avr/io.h>
#include "digio.h"
#include "pins.h"

void ledOn(uint8_t pin)
{
	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
	*(mapping->in_register) |= mask;
	*(mapping->out_register) |= mask;
/*
	//PIN 6 della porta E, comandato dal bit 4 di ogni registro
	//PINE non lo usiamo perché serve per l'ingresso
	const uint8_t mask=(1<<4);
	DDRE |=mask;
	PORTE |=mask;
*/
}



