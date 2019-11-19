#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "smarthouse_comm.h"
#include "smarthouse_globals.h"
#include "packet_handler.h"
#include "uart.h"
#include "uart_ORIGINAL.h"
//****
#include "digio.h"
//****
static struct UART* uart;
static PacketHandler packet_handler;

static uint16_t global_seq;

static PacketHeader* _initializeBuffer( PacketType type,
                                        PacketSize size,
                                        void* args )
{
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


void initializeOps(PacketType type, PacketSize size, PacketHandler* h, void* arg)
{
	PacketOperations ops =
	{
		type,
	       size,
	       _initializeBuffer,
	       (void*)h,
	       _onReceive,
	       (void*)arg,
	      };
	PacketHandler_installPacket(&packet_handler, &ops);
}


void Smarthouse_initializePackets(void)
{
	initializeOps(SYSTEM_PARAM_PACKET_ID,
			sizeof(SystemParamPacket),
			&packet_handler,
			&system_params);
	initializeOps(SYSTEM_STATUS_PACKET_ID,
			sizeof(SystemStatusPacket),
			&packet_handler,
			&system_status);
	initializeOps(TEST_PACKET_ID,
			sizeof(TestPacket),
			&packet_handler,
			&test);
	initializeOps(MESSAGE_PACKET_ID,
			sizeof(StringMessagePacket),
			&packet_handler,
			&string_message);
}

void Smarthouse_commInit (void)
{
	//baude rate definition is in smarthouse_globals.c
	uart = UART_init("uart_0", system_params.comm_speed);
	global_seq=0;
	//2)inizializzazione del packethandler
	PacketHandler_initialize(&packet_handler);
	Smarthouse_initializePackets();
}


//////////////////////////////TEST
PacketStatus Smarthouse_sendPacket(PacketHeader* p){
  p->seq=global_seq;
  PacketStatus status=PacketHandler_sendPacket(&packet_handler, p);    
  if (status==Success)
    ++system_status.tx_packets;
  else
    ++system_status.tx_packet_errors;
  return status;
}

void Smarthouse_flushInputBuffers(void)
{
	while (UART_rxBufferFull(uart))
	{
	    uint8_t c=UART_getChar(uart);
char buffer[128];
char* bend = buffer + sprintf(buffer, "%x\n", c);
UART_putChar(uart, (uint8_t) * bend);
	    PacketStatus status=PacketHandler_rxByte(&packet_handler, c);
		if(status<0)
		{
			printf("Errore\n");
		}
	}
}

int Smarthouse_flushOutputBuffers(void)
{
	while (packet_handler.tx_size)
	{
		UART_putChar(uart, PacketHandler_txByte(&packet_handler));
	}
	system_status.tx_buffer_size=UART_txBufferFull(uart);
	return packet_handler.tx_size;
}


void Smarthouse_commHandle(void)
{
	Smarthouse_flushInputBuffers();
	++global_seq;
/*	if(test.prova==1)
	{
		printf("Valore prova: %d\n", test.prova);
		DigIO_setDirection(10, 1);
		DigIO_setValue(10, 1);
	}
	else
	{
	printf("Valore prova: %d\n", test.prova);
	}
*/	Smarthouse_sendPacket((PacketHeader*)&test);
	Smarthouse_flushOutputBuffers();

}
