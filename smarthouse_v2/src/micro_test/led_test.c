#include <stdio.h>
#include "smarthouse_functions.h"
#include "packet_operations.h"
#include "smarthouse_packets.h"
#include "digio.h"
#include "pwm.h"
#include "adc.h"
#include "uart.h"
int main(int argc, char **argv)
{
	DigIO_init();
	Adc_init();
	PWM_init();
	uint32_t baud = 19200;
	UART_init("uart_0", baud);
	printf_init();	
while(1)
{	Digital_init(DigitalLed, 11);
	Digital_init(DigitalInput, 10);
//	Analog_init();
}
	return 0;
}	
