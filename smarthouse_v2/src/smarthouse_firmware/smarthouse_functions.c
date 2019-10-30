#include <stdio.h>
#include "smarthouse_functions.h"
#include "smarthouse_packets.h"
#include "digio.h"
#include "pwm.h"
#include "delay.h"
#include "adc.h"

void LedOn(uint8_t);
void LedOff(uint8_t);
void Dimmer(uint8_t);
void InputDigital(uint8_t);

PacketStatus Digital_init(DigitalType type, uint8_t pin)
{
	switch(type)
	{
		case DigitalLed:
			LedOn(pin);
		case DigitalDimmer:
			Dimmer(pin);
		case DigitalInput:
			InputDigital(pin);
		case DigitalOff:
			LedOff(pin);
		default:
			return -1;
	}
	return Success;
}

void LedOn(uint8_t pin)
{
	DigIO_init();
	DigIO_setDirection(pin, Output);
	DigIO_setValue(pin, 1);
}

void LedOff(uint8_t pin)
{
	DigIO_init();
	DigIO_setDirection(pin, Output);
	DigIO_setValue(pin, 0);
}

void Dimmer(uint8_t pin)
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
