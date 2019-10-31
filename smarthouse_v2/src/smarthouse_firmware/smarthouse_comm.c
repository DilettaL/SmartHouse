#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "smarthouse_comm.h"
#include "smarthouse_packets.h"
#include "smarthouse_globals.h"
#include "uart.h"

void Smarthouse_commInit(void)
{
	//1)il baude rate deve essere preso dal pacchetto SystemParams
	uart = UART_init("uart_0", system_params.comm_speed);
	//2)inizializzazione del packethandler
	//3)funzione interna a questo file che installa i pacchetti
	//Smarthouse_initializePackets
}
