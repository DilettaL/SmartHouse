//Librerie
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "switch_dimmer.h"
#include "uart.h"

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
	//Set TCCR3 and channel B (pag 82)
 	TCCR3A=TCCRA_MASK;
	TCCR3B=TCCRB_MASK;
	//Set Compare Register
	OCR3BH=0;
	OCR3BL=1;
	//PIN 6 porta E, collegato all'OSC3
	const uint8_t mask=(1<<4);
	DDRE |= mask;
	uint8_t intensity=200;
	while(1)
	{
		OCR3BL=intensity; 
		_delay_ms(100);
		//intensity+=8;
	}
}

void DigitalInput(void)
{

//UTILIZZARE SOLO PIN CHE UNANO PIN CHANGE!!

  // this initializes the printf/uart thingies
  printf_init(); 

  // we connect the switch to pin 12
  // that is the bit 6 of port b
  
  const uint8_t mask=(1<<6);
  // we configure the pin as input, clearing the bit 6
  DDRB &= ~mask;
  
  // we enable pullup resistor on that pin
  PORTB |= mask;
  
  while(1){
    int key=(PINB&mask)==0; // we extract the bit value of the 6th bit
    printf("switch %02x, %d\n", (int) PORTB, key);
    _delay_ms(500); // from delay.h, wait 1 sec
  }
}
