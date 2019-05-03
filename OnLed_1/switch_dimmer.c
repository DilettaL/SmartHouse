//Librerie
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "switch_dimmer.h"

#define TCCRA_MASK (1<<WGM30)|(1<<COM3B0)|(1<<COM3B1)
#define TCCRB_MASK ((1<<WGM32)|(1<<CS30))   

//Pin fisici che supportano pwm 26-25-24-23-18-17-16-15-5-1-7-6
void Led_On(void)
{
	//PIN 6 della porta E, comandato dal bit 4 di ogni registro
	//PINE non lo usiamo perché serve per l'ingresso
	const uint8_t mask=(1<<4);
	DDRE |=mask;
	PORTE |=mask;
}

void Led_Dimmer(void)
{
	//Set TCCR3 and channel B
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
}
