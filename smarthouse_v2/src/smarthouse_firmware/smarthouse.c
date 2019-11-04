#include <stdio.h>
#include "digio.h"
#include "adc.h"
#include "pwm.h"
#include "smarthouse_comm.h"
#include "smarthouse_param.h"
//NON SO SE SERVE PERCHE' FORSE SI FA IN PARAMINIT#include "smarthouse_pin.h"
//******************
//#include "smarthouse_functions.h"
#include "packet_operations.h"
#include "smarthouse_packets.h"
//******************
int main(int argc, char **argv)
{
	//Initialization low level functions
	DigIO_init();
	Adc_init();
	PWM_init();
	//Initialization high level smarthouse firmware functions
	Smarthouse_commInit();	//Uart and common initialization
	Smarthouse_paramInit();	//EEPROM(firmware, protocol, analog and digital pins) initialization
//	Smarthouse_pinInit();	//Struct digital and analog initialization questa cosa potrei farla in smartfuncions

/*************
Dopo di ciò può iniziare il programma vero e proprio
	while(1)
	{
		//POSSIAMO SCOMMENTARLA SOLO DOPO L'HANDLER
		Smarthouse_flushInputBuffers();
//Controllo il tipo di pacchetto, se pacchetto di configurazione(da ricevere) o pacchetto di stato (da 	trasmettere). Nel caso di pacchetto di stato bisogna abilitare la Smarthouse_flushOutoputBuffers(); e inviare il pacchetto desiderato dal pc
	}
*************/
/*	AnalogConfig test;
	for(int i=0; i<ANALOG_MAX; i++)
	{
		if(i=10) {test->Adc[i]=1;	}
		else{test->Adc[i]=0;}
	}	
	test->samples=100;
	Analog_init(test);
*/
//DA RIVEDERE
/*	DigitalConfig *test;
	test->type= DigitalLed;
	for(int i=0; i<DIGITAL_MAX; i++)
	{
		if(i==10) {test->led[i]=1;	}
		else{test->led[i]=0;}
	}
	Digital_init(test);*/	
	return 0;
}

/*
PacketStatus Digital_init(DigitalConfig digital)
{
	switch(digital->type)
	{
		case DigitalLed:
			Led(digital->*ledOn);
		case DigitalDimmer:
			Dimmer(digital->*dimmer);
		case DigitalInput:
			InputDigital(digital->*input, digital->intensity);
		case DigitalOff:
			LedOff(digital->*ledOff);
		default:
			return -1;
	}
	return Success;
}

void LedOn(uint8_t *pin)
{
	for(int i=0; i<DIGITAL_MAX; i++)
	{
		if(pin[i]==1)
		{
			DigIO_setDirection(i, Output);
			DigIO_setValue(i, 1);
		}
	}
}

void LedOff(uint8_t *pin)
{
	for(int i=0; i<DIGITAL_MAX; i++)
	{
		if(pin[i]==1)
		{
			DigIO_setDirection(i, Output);
			DigIO_setValue(i, 0);
		}
	}
}

void Dimmer(uint8_t *pin, uint8_t intensity)
{	
	for(int i=0; i<DIGITAL_MAX; i++)
	{
		if(pin[i]==1)
		{
			PWM_enable(i, 1);
			PWM_setDutyCycle(i, intensity);
			delayMs(100);
		}
	}
}

void InputDigital(uint8_t *pin)
{
	for(int i=0; i<DIGITAL_MAX; i++)
	{
		if(pin[i]==1)
		{
			DigIO_setDirection(i, Input);
			DigIO_setValue(i, 1);
			uint8_t key=DigIO_getValue(i);
			printf("%d", key);
		}	
	}
}

PacketStatus Analog_init(AnalogConfig analog)
{
	for(int i=0; i<ANALOG_MAX; i++)
	{
		if(analog->Adc[i]==1)
		{	
			SetAdc(i);
		}
		RunAdc(analog->samples);
	}
	return Success;
}
*/
