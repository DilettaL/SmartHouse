#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"
#include "uart.h"
#include "pins_adc.h"


void adc_init()
{
	//Defalut right adjust mode
/*PROVVISORIO*/	//Reference selection (supply) =1.1V internal e capacità esterna su AREF
	ADMUX= (1<<REFS1)|(0<<REFS0);
}
//In ingresso alla funzione adc run dovrà esere presente il valore del pin che per ora inseriamo nella prima riga di codice
void adc_run()
{
	//Define input adc channel
/*PROVVISORIO*/int pin_input=0;
/*PROVVISORIO*/int numb_samples=10;
	int count;
	pins[pin_input].select_adc;
	//Configurare eventuali trigger
	//ADC Enable
	ADCSRA=(1<<ADEN);
//start conversion se si è in free running mode (lo si abilita una volta e poi va in automatico)
	ADCSRA=(1<<ADSC);
	//Definire quanti campioni per misura si vogliono acquisire
	for(count=0; count<numb_samples; count++)
	{
		//start conversion
//si posiziona qui se conversione in single mode ogni volta deve essere riabilitato
/*PROVVISORIO*/	ADCSRA=(1<<ADSC);
	//Verifica termine conversione
	//Memorizzazione dato acquisito
	//Lettura + memorizzazione
	//Pulizia eventuali registri
	}
	
}

