#include <stdio.h>
#include "smarthouse_functions.h"
#include "smarthouse_packets.h"
#include "digio.h"
#include "pwm.h"

void Led(void);
void Dimmer(void);

PacketStatus Digital_init(DigitalType type)
{
	switch(type)
	{
		case DigitalLed:
			Led();
		case DigitalDimmer:
			Dimmer();
		case DigitalInput:
			printf("DigitalInput\n");
		default:
			return -1;
	}
}

void Led(void)
{
	PWM_init();
	DigIO_setDirection(10, Output);
	DigIO_setValue(10, 1);
}

void Dimmer(void)
{
	PWM_enable(10, 1);
	PWM_setDutyCycle(10, 120);
}
