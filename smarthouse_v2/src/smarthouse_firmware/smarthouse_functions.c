#include <stdio.h>
#include "smarthouse_functions.h"
#include "smarthouse_packets.h"
#include "digio.h"
#include "pwm.h"
#include "delay.h"
#include "adc.h"

void Led(void);
void Dimmer(void);
void InputDigital(void);

PacketStatus Digital_init(DigitalType type)
{
	switch(type)
	{
		case DigitalLed:
			Led();
		case DigitalDimmer:
			Dimmer();
		case DigitalInput:
			InputDigital();
		default:
			return -1;
	}
	return Success;
}

void Led(void)
{
	DigIO_init();
	DigIO_setDirection(10, Output);
	DigIO_setValue(10, 1);
}

void Dimmer(void)
{	
	PWM_init();
	PWM_enable(10, 1);
	PWM_setDutyCycle(10, 10);
	delayMs(100);
}

void InputDigital(void)
{
	DigIO_init();
	DigIO_setDirection(10, Input);
	DigIO_setValue(10, 1);
	uint8_t key=DigIO_getValue(10);
	printf("%d", key);	
}

PacketStatus Analog_init(void)
{
	Adc_init();
	SetAdc(4);
	RunAdc(10);
	return Success;
}
