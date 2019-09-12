#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "digio.h"
#include "pins.h"
#include "uart.h"
/*TEST*/
#include <avr/interrupt.h>


void initDimmer(void)
{
	//PWM_init
	//interrupt
	TIMSK0=0;
	TIMSK1=0;
	TIMSK2=0;
	TIMSK3=0;
	TIMSK4=0;
	//Timer0
	TCCR0A=(1<<WGM00)|(1<<WGM01);
	TCCR0B=(1<<CS00);
	//Timer1 (fast pwm, no inverted, 16MHz)
	TCCR1A=(1<<WGM10);
 	TCCR1B=(1<<WGM12)|(1<<CS10);
	//Timer2
	TCCR2A=TCCR0A;
  	TCCR2B=TCCR0B;
	//Timer3
	TCCR3A=TCCR1A;
  	TCCR3B=TCCR1B;
	//Timer4
	//Timer5
	
}

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
	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
	//PWM_setOutput
	*(mapping->dir_register) |= mask;
	*(mapping->tcc_register) |= (mapping->com_mask);
	//PWM_dutyCycle
	*(mapping->oc_register)=intensity;
/*	while(1)
	{
test	printf("v %u\n", *(mapping->oc_register));
		_delay_ms(1000);
		*(mapping->oc_register)+=intensity;
	}
*/
}

void digitalInput(uint8_t pin)
{
	// this initializes the printf/uart thingies
	printf_init(); 
	const Pin* mapping=pins+pin;
	uint8_t mask=1<<mapping->bit;
	*(mapping->dir_register) |=mask; //dovrebbe essere equivalente a &=~
	*(mapping->out_register) |=mask; //in questo caso si attiva il resistore di pull up essendo il pin un ingresso	

		int key=(*(mapping->in_register) & mask)==0;
/*dato che il risultato viene messo direttamente in in_register non ho capito perché ha inserito key e le altre cose*/
		printf("switch: %d\n", key);
}

