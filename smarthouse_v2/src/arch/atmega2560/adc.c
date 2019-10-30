#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"
#include "uart.h"
#include "pins.h"
#include <avr/interrupt.h>

//ADMUX è stato completamente configurato in modo provvisorio
//ADCSRA è stato completamente configurato in modo provvisorio
//ADCSRB è stato completamente configurato in modo provvisorio

void Adc_init()
{
	//Defalut right adjust mode
	//Reference selection (supply) =1.1V internal e capacità esterna su AREF
	ADMUX= (1<<REFS1)|(0<<REFS0);
	//ADC Enable
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

void SetAdc(uint8_t pin)
{
	//Define input adc channel
	const Pin_analog* mapping=pins_analog+pin;
	//pins set MUX5:0 of ADMUX and ADCSRB register
	ADMUX |= (mapping->select_adc_mux);
	ADCSRB |= (mapping->select_adc_adcsrb);
}

uint16_t RunAdc(uint8_t numb_samples)
{
	//Each data is converts with n samples
	uint16_t result[numb_samples];
	uint8_t count;
	for(count=0; count<numb_samples; count++)
	{
		// start single convertion
		// write ’1′ to ADSC
		ADCSRA |= (1<<ADSC);
		while( ADCSRA & (1<<ADSC) );
		result[count]=ADC;
/*test*/	printf("result[%d]:%d\n", count, result[count]);
	}
	return *result;	
}
