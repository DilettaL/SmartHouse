#include <stdio.h>
#include "packet_handler.h"
#include "smarthouse_packets.h"
#include "uart.h"
#include "delay.h"
#include <string.h>
#include "smarthouse_globals.h"
#include "digio.h"

static struct UART* uart;
static PacketHandler packet_handler;

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

void flushBuffers(void) {
  // we read all what we have to read
  while (UART_rxBufferFull(uart))
    PacketHandler_rxByte(&packet_handler, UART_getChar(uart));
  // we write all what we have to write
  while (packet_handler.tx_size)
    UART_putChar(uart, PacketHandler_txByte(&packet_handler));
}

int main(int argc, char**argv)
{
	DigIO_init();
	int seq = 0;
	uart = UART_init(0, 115200);
	PacketHandler_initialize(&packet_handler);
	PacketOperations packet_ops = 
	{
		TEST_PACKET_ID,
		sizeof(TestPacket),
		_initializeBuffer,
		(void*)&packet_handler,
		_onReceive,
		(void*)&packet_handler
	};
//	TestPacket test = {.prova=1};
	PacketHandler_installPacket(&packet_handler, &packet_ops);
  	while(1)
	{
		while (PacketHandler_sendPacket(&packet_handler, (PacketHeader*) & test) != Success)
		{
			flushBuffers();
			if(test.prova==0)
			{
				DigIO_setDirection(10, 1);
				DigIO_setValue(10, 1);
			}
		}
	test.header.seq = seq;
	seq++;
	}
	delayMs(100);
}
