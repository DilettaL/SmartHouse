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
#include "delay.h"
//****
static struct UART* uart;
static PacketHandler packet_handler;

static uint16_t global_seq;

//Per debug:
void printString(char* s) {
int l = strlen(s);
for (int i = 0; i < l; ++i, ++s)
UART_putChar(uart, (uint8_t) * s);
}
///////////////////////////////////


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
char buffer2[128];
char *bend2=buffer2+sprintf(buffer2, "elementi di ingresso:\n");
	while (UART_rxBufferFull(uart))
	{
		uint8_t c=UART_getChar(uart);
bend2+= sprintf(bend2, "%x\t", c);
	    	PacketStatus status=PacketHandler_rxByte(&packet_handler, c);
		if(status<0)
		{
			printf("Errore\n");
		}
bend2+=sprintf(bend2, "prova\n");
	}
	printString(buffer2);
	delayMs(1000);
}

/*int Smarthouse_flushOutputBuffers(void)
{
	while (packet_handler.tx_size)
	{
		UART_putChar(uart, PacketHandler_txByte(&packet_handler));
	}
	system_status.tx_buffer_size=UART_txBufferFull(uart);
	return packet_handler.tx_size;
}
*/



void Smarthouse_commHandle(void)
{
char buffer[128];
char* bend;
bend = buffer + sprintf(buffer, "prova=");
bend+= sprintf(bend, "%d\n", test.prova);
printString(buffer);
	Smarthouse_flushInputBuffers();
	if(test.prova!=0)
	{
//bend+= sprintf(bend, "ACCENDI LED\n");
//		DigIO_setDirection(10, 1);
//		DigIO_setValue(10, 1);
	}
	else
	{
//bend+= sprintf(bend, "errore\n");
//		DigIO_setValue(10, 0);
	}
/*	Smarthouse_sendPacket((PacketHeader*)&test);
	Smarthouse_flushOutputBuffers();
*/
}
