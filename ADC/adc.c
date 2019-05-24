#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"
#include "uart.h"
#include "pins_adc.h"

//ADMUX è stato completamente configurato in modo provvisorio
//ADCSRA è stato completamente configurato in modo provvisorio
//ADCSRB è stato completamente configurato in modo provvisorio

void adc_init()
{
	//Defalut right adjust mode
/*PROVVISORIO*/	//Reference selection (supply) =1.1V internal e capacità esterna su AREF
	ADMUX= (1<<REFS1)|(0<<REFS0);
	//If we use Single Mode Conversion we must delete next lines
	//Set autotrigger mode (free running, ecc..), but previously we able the ADTS bit selection with ADCSRA register
/*PROVVISORIO*///ADCSRA=(1<<ADATE);	
	//da controllare se giusto inserirlo qui
/*PROVVISORIO*///ADCSRB=(<<ADTS2)|(<<ADTS1)|(<<ADTS0);
//Si configura il prescaler (per ora non si definisce un valore)
/*PROVVISORIO*///ADCSRA=(<<ADPS2)|(<<ADPS1)|(<<ADPS0);
}
//In ingresso alla funzione adc run dovrà esere presente il valore del pin che per ora inseriamo nella prima riga di codice
void adc_run()
{
	//Define input adc channel
/*PROVVISORIO*/int pin_input=0;
/*PROVVISORIO*/int numb_samples=10;
	//Each data is converts with 10 sample
	float result[10];
	int count;
	//pins set MUX5:0 of ADMUX and ADCSRB register
	pins[pin_input].select_adc;
	//Configurare eventuali trigger
//Se si è nella modalità autotrigger bisogna abilitare questo bit a 1
/*PROVVISORIO*///ADCSRA=(1<<ADATE);
	//ADC Enable
	ADCSRA=(1<<ADEN);
//Non so se va applicato qui, si abilita l'interrupt che definisce il termine della conversione
/*PROVVISORIO*///ADCSRA=(1<<ADIE);
	//start conversion
//se si è in free running mode (lo si abilita una volta e poi va in automatico)
/*PROVVISORIO*///ADCSRA=(1<<ADSC);
	//Definire quanti campioni per misura si vogliono acquisire
	for(count=0; count<numb_samples; count++)
	{
		//start conversion
//si posiziona qui se conversione in single mode ogni volta deve essere riabilitato
/*PROVVISORIO*///ADCSRA=(1<<ADSC);
		//Check conversion end
		while(ADCSRA.ADIF==1)
		{
			//Conversion is complete, now we can read and save the data
			//ADCL register
			for(count=0; count<=7; count++)
			{
				//Operations for single mode conversion and right adjust configuration
//Per differential mode conversion o left adjust mode ----> operazioni diverse nel caso (pag 280)
/*DA CONTROLLARE ADCL[COUNT]POTREBBE NON ESSERE GIUSTO*///result[count]=ADCL[count]*1024/(1.1);
			}
			//ADCH register
			for(count=8; count<=9; count++);
			{
				//Operations for single mode conversion and right adjust configuration
//Per differential mode conversion o left adjust mode ----> operazioni diverse nel caso (pag 280)
/*DA CONTROLLARE ADCL[COUNT]POTREBBE NON ESSERE GIUSTO*///result[count]=ADCH[count]*1024/(1.1);
			}
		}
	//Pulizia eventuali registri
	}
	
}

