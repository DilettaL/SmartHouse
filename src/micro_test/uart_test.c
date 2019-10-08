#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	uart=UART_init("uart_0",115200);
	while(1)
	{
		char tx_message[300];
		char rx_message[300];
		rx_message[0]=0;
		int size=0, l, i;
		uint8_t *s;
		while(1)
		{
			sprintf(tx_message, "msg: [%s]\n", rx_message);
			l=strlen(s);
  			for(int i=0; i<l; ++i, ++s)
  			{
				UART_putChar(uart, s);
			}
			uint8_t c= UART_getChar(uart);
			rx_message[size]=c;
	      		++size;
	      		rx_message[size]=0;
	      		if (c == 0xFF ||c == '\n' || c=='\r' || c==0)
			{
				break;
	      		} 	     
			_delay_ms(10);
		}
	}
	return 0;
}
