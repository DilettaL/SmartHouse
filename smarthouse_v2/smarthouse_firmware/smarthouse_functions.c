#include "adc.h"
#include "digio.h"
#include "smarthouse_functions.h"
//queste librerie dovranno poi essere messe in common
#include "smarthouse_avr_common.h"


//3) Dichiaro le funzioni di basso livello che permettono di effettuare le operazioni sui pin
//3a)
void led(struct PDigital*, uint8_t);
//3a)
void led(PDigital* digital, pin)
{
	//set the pin as output
	DigIO_setDirection(pin, digital->dir);
	//set the value of the pin
	DigIO_setValue(pin, digital->value);
}

//1) Implemento funzione che richiama, dipendentemente dal tipo ledOn
//2) La struct di tipo PDigital è dichiarata in smarthouse_functions.h
PacketStatus Digital_Pin(struct PDigital* digital, const DigitalType type, int8_t* pins)
{
	switch(type)
	{
		case DigitalTypeLed:
			return led(digital, pins);
/*
		case DigitalTypeDimmer:
			return
		case DigitalTypeInput:
			return
*/		default:
			return -1;
	}
}
