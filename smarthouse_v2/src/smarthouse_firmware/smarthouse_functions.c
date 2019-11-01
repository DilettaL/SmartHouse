#include <stdio.h>
#include "smarthouse_functions.h"
#include "packet_operations.h"
#include "smarthouse_packets.h"
#include "digio.h"
#include "pwm.h"
#include "delay.h"
#include "adc.h"

//*************
#include "buffer_utils.h"
#include "uart.h"
#include <string.h>
#include "uart_ORIGINAL.h"
//*************

void LedOn(uint8_t);
void LedOff(uint8_t);
void Dimmer(uint8_t);
void InputDigital(uint8_t);
uint16_t AdcConvert(uint8_t);


//***************
struct UART* uart;
//***************


PacketStatus Digital_init(DigitalType type, uint8_t pin)
{
	switch(type)
	{
		case DigitalLed:
			LedOn(pin);
			break;
		case DigitalDimmer:
			Dimmer(pin);
			break;
		case DigitalInput:
			InputDigital(pin);
			break;
		case DigitalOff:
			LedOff(pin);
			break;
		case Adc:
			AdcConvert(pin);
			break;
		default:
			return -1;
	}
	return Success;
}

void LedOn(uint8_t pin)
{
	DigIO_setDirection(pin, Output);
	DigIO_setValue(pin, 1);
}

void LedOff(uint8_t pin)
{
	DigIO_setDirection(pin, Output);
	DigIO_setValue(pin, 0);
}

void Dimmer(uint8_t pin)
{	
	PWM_enable(pin, 1);
	PWM_setDutyCycle(pin, 100);
	delayMs(100);
}

void InputDigital(uint8_t pin)
{
	DigIO_setDirection(pin, Input);
	DigIO_setValue(pin, 1);
	uint8_t key=DigIO_getValue(pin);
	printf("value:%d\n",key);	
}

uint16_t AdcConvert(uint8_t pin){
	uint16_t value = 0;
	uint8_t sample = 10;
	SetAdc(pin);
	value = RunAdc(sample);
//solo come test:
//	for (int i = 0; i < sample; i++);
//		printf ("value: %d\n",value);
	return value;
}

/*
PacketStatus Analog_init(void)
{
	SetAdc(4);
	RunAdc(10);
	return Success;
}
*/

