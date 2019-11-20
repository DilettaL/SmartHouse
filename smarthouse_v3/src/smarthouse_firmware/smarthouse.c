#include <stdio.h>
#include "smarthouse_comm.h"
#include "digio.h"
/////////////////////////////////////
#include <string.h>
#include "uart.h"

static struct UART* uart;

int main (int argc, char** argv)
{
	DigIO_init();
	Smarthouse_commInit();
char buffer[5];
char *bend=buffer+sprintf(buffer, "PROVA");
int l=strlen(bend);
for(int i=0; i<l; ++i, ++bend)
{
	UART_putChar(uart, (uint8_t)*bend);
}
	while(1)
	{
		Smarthouse_commHandle();
	}
	return 0;
}
