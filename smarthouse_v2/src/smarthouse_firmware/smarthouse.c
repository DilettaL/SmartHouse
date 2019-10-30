#include <stdio.h>
#include "smarthouse_functions.h"
#include "smarthouse_packets.h"

int main(int argc, char **argv)
{
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
			Led(digital->*led);
		case DigitalDimmer:
			Dimmer(digital->*dimmer);
		case DigitalInput:
			InputDigital(digital->*input);
		default:
			return -1;
	}
	return Success;
}

void Led(uint8_t *pin)
{
	DigIO_init();
	for(int i=0; i<DIGITAL_MAX; i++)
	{
		DigIO_setDirection(i, Output);
		DigIO_setValue(i, led[i]);
	}
}

void Dimmer(uint8_t *pin)
{	
	PWM_init();
	PWM_enable(pin, 1);
	PWM_setDutyCycle(pin, 10);
	delayMs(100);
}

void InputDigital(uint8_t pin)
{
	DigIO_init();
	DigIO_setDirection(pin, Input);
	DigIO_setValue(pin, 1);
	uint8_t key=DigIO_getValue(pin);
	printf("%d", key);	
}

PacketStatus Analog_init(void)
{
	Adc_init();
	SetAdc(4);
	RunAdc(10);
	return Success;
}
*/
