#include <stdio.h>
#include "smarthouse_functions.h"
#include "smarthouse_packets.h"
#include "digio.h"

void Led(void);

PacketStatus Digital_init(DigitalType type)
{
	switch(type)
	{
		case DigitalLed:
			Led();
		case DigitalDimmer:
			printf("DigitalDimmer\n");
		case DigitalInput:
			printf("DigitalInput\n");
		default:
			return -1;
	}
}

void Led(void)
{
	DigIO_setDirection(10, Output);
	DigIO_setValue(10, 1);
}
