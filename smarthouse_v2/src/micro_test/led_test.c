#include <stdio.h>
#include "smarthouse_functions.h"
#include "packet_operations.h"
#include "smarthouse_packets.h"

int main(int argc, char **argv)
{
	Digital_init(DigitalLed, 11);
	Digital_init(DigitalInput, 10);
//	Analog_init();
	return 0;
}	
