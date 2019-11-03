#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "smarthouse_comm.h"
#include "smarthouse_globals.h"
#include "packet_handler.h"
#include "packet_operations.h"
#include "uart.h"

static struct UART* uart;
static uint16_t global_seq;
static PacketHandler packet_handler;

void Smarthouse_initializePackets(void);

void Smarthouse_commInit(void)
{
	//baude rate definition is in smarthouse_globals.c
	uart = UART_init("uart_0", system_params.comm_speed);
	global_seq=0;
	//2)inizializzazione del packethandler
	PacketHandler_initialize(&packet_handler);
	//3)funzione interna a questo file che installa i pacchetti
	Smarthouse_initializePackets();
}

void Smarthouse_initializePackets(void)
{
	//In this function we install all packets
	//We call PacketHandler_installPacket for all packet
	//Packet 1
	PacketHandler_installPacket(&packet_handler,
					SYSTEM_PARAM_PACKET_ID
	);
	//Packet 2
	PacketHandler_installPacket(&packet_handler,
					DIGITAL_PARAM_PACKET_ID
	);
	//Packet 3
	PacketHandler_installPacket(&packet_handler,
					ANALOG_PARAM_PACKET_ID
	);
}
