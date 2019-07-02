#include <avr/io.h>
#include <util/delay.h>
#include "digio.h"
#include "pins.h"

void ledOn(uint8_t pin)
{
	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register) |= mask;
	*(mapping->out_register) |= mask;
}

void ledDimmer(uint8_t pin, uint8_t intensity)
{
	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
/*
#define TCCRA_MASK (1<<WGM30)|(1<<COM3B0)|(1<<COM3B1)
#define TCCRB_MASK ((1<<WGM32)|(1<<CS30))   
//Set TCCR3 and channel B (pag 82)
 	TCCR3A=TCCRA_MASK;
	TCCR3B=TCCRB_MASK;
	//Set Compare Register
	OCR3BH=0;
	OCR3BL=1;
	//PIN 6 porta E, collegato all'OSC3
	const uint8_t mask=(1<<4);
	DDRE |= mask;
	uint8_t intensity=0;
	while(1)
	{
		OCR3BL=intensity; 
		_delay_ms(100);
		intensity+=8;
	}
*/
}

