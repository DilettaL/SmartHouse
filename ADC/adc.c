#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"
#include "uart.h"

//pin adc arduino da 82 a 97
//pin adc board da 0 a 15 tutti analog input

void adc(void)
{
	//Configurazione
	//Conversion starts ADCSRA.ADSC=1 tutta durata conversione
	//Questa modalità perché decide il pc quando prelevare il valore
}
