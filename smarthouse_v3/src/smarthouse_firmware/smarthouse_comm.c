#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "smarthouse_comm.h"
#include "smarthouse_globals.h"
#include "packet_handler.h"
#include "uart.h"

static struct UART* uart;
static PacketHandler packet_handler;

void Smarthouse_commInit (void){
	//baude rate definition is in smarthouse_globals.c
	uart = UART_init("uart_0", system_params.comm_speed);
	//2)inizializzazione del packethandler
	PacketHandler_initialize(&packet_handler);
	Smarthouse_initializePackets();
}

void Smarthouse_initializePackets(void){
	initializeOps(SYSTEM_PARAM_PACKET_ID,
			sizeof(SystemParamPacket),
			&packet_handler,
			&system_param);
}

void initializeOps(PacketType type, PacketSize size, PacketHandler* h, void* arg){
	PacketOperations ops = {type,
	       size,
	       _initializeBuffer,
	       (void*)h,
	       _onReceive,
	       (void*)arg,
	      };
	PacketHandler_installPacket(&packetHandler, &ops);
}

static PacketHeader* _initializeBuffer( PacketHandler* h,
                                        PacketSize size,
                                        void* args ){
	  PacketHandler* handler=(PacketHandler*) args;
	return (PacketHeader*) handler->rx_current_packet;
}

static PacketStatus _onReceive(PacketHeader *packet, void* arg)
{
	PacketHandler *handler=(PacketHandler*)arg;
//arg deve essere un riferimento alla struc di globals
//packet è il packetheader di quel pacchetto (risultato di intiaizeBuffer) che è stato ricevuto e va copiato in memoria
	memcpy(handler, packet, packet->size);
	return Success;
}
