#include <stdio.h>
#include "smarthouse_functions.h"
#include "smarthouse_packets.h"

int main(int argc, char **argv)
{
	DigIO_init();
	Adc_init();
	PWM_init();
/*	AnalogConfig test;
	for(int i=0; i<ANALOG_MAX; i++)
	{
		if(i=10) {test->Adc[i]=1;	}
		else{test->Adc[i]=0;}
	}	
	test->samples=100;
	Analog_init(test);
*/
	DigitalConfig test;
	test->type= DigitalLed;
	for(int i=0; i<DIGITAL_MAX; i++)
	{
		if(i=10) {test->led[i]=1;	}
		else{test->led[i]=0;}
	}
	Digital_init(test);	
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