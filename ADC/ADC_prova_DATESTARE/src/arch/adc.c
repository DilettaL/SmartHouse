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

void adc_init()
{
//SREG |= (1<<7); 
	//Defalut right adjust mode
/*PROVVISORIO*/	//Reference selection (supply) =1.1V internal e capacità esterna su AREF
	ADMUX= (1<<REFS1)|(0<<REFS0);
	//ADC Enable
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
//Si configura il prescaler (per ora non si definisce un valore)
/*PROVVISORIO*///ADCSRA=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);


	//If we use Single Mode Conversion we must delete next lines
	//Set autotrigger mode (free running, ecc..), but previously we able the ADTS bit selection with ADCSRA register
/*PROVVISORIO*///ADCSRA=(1<<ADATE);	
	//da controllare se giusto inserirlo qui
/*PROVVISORIO*///ADCSRB=(<<ADTS2)|(<<ADTS1)|(<<ADTS0);
}

uint16_t adc_run(uint8_t pin, uint8_t numb_samples)
{
	//Define input adc channel
	const Pin_analog* mapping=pins_analog+pin;
	//pins set MUX5:0 of ADMUX and ADCSRB register
//DUBBIO
	ADMUX |= (mapping->select_adc_mux);
	ADCSRB |= (mapping->select_adc_adcsrb);
//fine dubbio
	//uint8_t numb_samples
	//Each data is converts with n samples
	uint16_t result[numb_samples];
	uint8_t count;
	//Configurare eventuali trigger
//Se si è nella modalità autotrigger bisogna abilitare questo bit a 1
/*PROVVISORIO*///ADCSRA=(1<<ADATE);
//Non so se va applicato qui, si abilita l'interrupt che definisce il termine della conversione
/*PROVVISORIO*/
	//start conversion
//se si è in free running mode (lo si abilita una volta e poi va in automatico)
/*PROVVISORIO*///ADCSRA=(1<<ADSC);

/*Test: tolto per vedere se è automatico*/
//ADCSRA=(1<<ADIE);
	for(count=0; count<numb_samples; count++)
	{
		// start single convertion
		// write ’1′ to ADSC
		ADCSRA |= (1<<ADSC);
		while( ADCSRA & (1<<ADSC) );
		result[count]=ADC;
		printf("result[%d]:\t%d\n", count, result[count]);
//Operations for single mode conversion and right adjust configuration
//Per differential mode conversion o left adjust mode ----> operazioni diverse nel caso (pag 280)
/*DA CONTROLLARE ADCL[COUNT]POTREBBE NON ESSERE GIUSTO*///
//Operations for single mode conversion and right adjust configuration
//Per differential mode conversion o left adjust mode ----> operazioni diverse nel caso (pag 280)
	//Pulizia eventuali registri
	}
	return *result;	
}

