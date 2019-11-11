#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "smarthouse_comm.h"
#include "uart.h"

static struct UART* uart;
static PacketHandler packet_handler;

void Smarthouse_commInit (void){
	//baude rate definition is in smarthouse_globals.c
	uart = UART_init("uart_0", system_params.comm_speed);

}
