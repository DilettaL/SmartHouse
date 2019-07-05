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
	*(mapping->oc_register_high)=0;
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register) |= mask;	
	while(1)
	{
		*(mapping->oc_register_low)=intensity;
		_delay_ms(100);
		intensity+=8;
	}
}

void digitalInput(void)
{

//UTILIZZARE SOLO PIN CHE UNANO PIN CHANGE!!

  // this initializes the printf/uart thingies
//  printf_init(); 

	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register)&=~ mask;
	*(mapping->out_register)|= mask;
	while(1)
	{
		//uint8_t result= *(mapping->in_register);		
		int key=(PINB&mask)==0; // we extract the bit value of the 6th bit
		//printf("switch %02x, %d\n", (int) PORTB, key);
		//_delay_ms(500); // from delay.h, wait 1 sec
	}
}

