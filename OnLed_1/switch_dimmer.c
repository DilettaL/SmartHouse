//Librerie
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "switch_dimmer.h"

//Pin fisici che supportano pwm 26-25-24-23-18-17-16-15-5-1-7-6
void Led_On(void)
{
	//PIN 6 della porta E, comandato dal bit 4 di ogni registro
	//PINE non lo usiamo perché serve per l'ingresso
	const uint8_t mask=(1<<4);
	DDRE |=mask;
	PORTE |=mask;
}
