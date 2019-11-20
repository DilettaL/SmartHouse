#include <stdio.h>
#include "smarthouse_comm.h"
#include "digio.h"
/////////////////////////////////////
#include <string.h>
#include "uart.h"

static struct UART* uart;

void printString(char* s) {
int l = strlen(s);
for (int i = 0; i < l; ++i, ++s)
UART_putChar(uart, (uint8_t) * s);
}

int main (int argc, char** argv)
{
char buffer[128];
char* bend = buffer + sprintf(buffer, "direction=[");
bend += sprintf(bend, "]\n");
bend += sprintf(bend, "value=[");
bend += sprintf(bend, "]\n");
printString(buffer);
/*	while(1)
	{
		Smarthouse_commHandle();
	}
*/	return 0;
}/home/diletta/Desktop/Sistemi Operativi/srrg2_orazio/srrg2_orazio/src/micro_test/digio_test.c
