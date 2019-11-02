#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "smarthouse_comm.h"
#include "smarthouse_globals.h"
#include "packet_operations.h"
#include "uart.h"

static struct UART* uart;
static uint16_t global_seq;

void Smarthouse_commInit(void)
{
	//baude rate definition is in smarthouse_globals.c
	uart = UART_init("uart_0", system_params.comm_speed);
	global_seq=0;
	//2)inizializzazione del packethandler
	//3)funzione interna a questo file che installa i pacchetti
	//Smarthouse_initializePackets
}
