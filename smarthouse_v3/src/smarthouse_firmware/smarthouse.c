#include <stdio.h>
#include "smarthouse_comm.h"
#include "digio.h"
/////////////////////////////////////
#include <string.h>
#include "uart.h"
#include "delay.h"

static struct UART* uart;

void printString(char* s) {
int l = strlen(s);
for (int i = 0; i < l; ++i, ++s)
UART_putChar(uart, (uint8_t) * s);
}

int main (int argc, char** argv)
{
while (1){
	char buffer[128];
	char* bend = buffer + sprintf(buffer, "direction=[");
	bend += sprintf(bend, "]\n");
	bend += sprintf(bend, "value=[");
	bend += sprintf(bend, "]\n");
	printString(buffer);
delayMs(500);
}
/*	while(1)
	{
		Smarthouse_commHandle();
	}
*/	return 0;
}
