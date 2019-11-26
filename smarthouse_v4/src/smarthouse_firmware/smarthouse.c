#include <stdio.h>
#include <string.h>
#include "packet_handler.h"
#include "digio.h"
#include "uart.h"
#include "delay.h"

static struct UART* uart;
static PacketHandler packet_handler;

//definiamo pacchetto
#pragma pack(push, 1)
typedef struct TestPacket{
	PacketHeader header;
	uint8_t prova;
} TestPacket;
#pragma pack(pop)

#define TEST_PACKET_ID 1

TestPacket test = { {TEST_PACKET_ID, sizeof(TestPacket), 0}, 0 }; 	//il campo "prova = 0";

TestPacket test_buffer;

PacketHeader* test_initializeBuffer(PacketType type, PacketSize size, void* args __attribute__((unused))) 
{
	if (type!=TEST_PACKET_ID || size!=sizeof(TestPacket))
		return 0;
	return (PacketHeader*) &test_buffer;
}

PacketStatus test_onReceive(PacketHeader* header, void* args __attribute__((unused))) 
{
	++header->seq;
	memcpy (&test_buffer, header, sizeof(TestPacket));
	return Success;
}

PacketOperations test_ops = {
	1,
	sizeof(TestPacket),
	test_initializeBuffer,
	0,
	test_onReceive,
	0
};

void flushInputBuffers(void) {
	while (UART_rxBufferFull(uart))
	{
		uint8_t c=UART_getChar(uart);
		PacketHandler_rxByte(&packet_handler, c);
	}
}

int flushOutputBuffers(void)
{
	while (packet_handler.tx_size)
		UART_putChar(uart, PacketHandler_txByte(&packet_handler));
	return packet_handler.tx_size;
}

int main (int argc, char** argv)
{
	DigIO_init();
	uart = UART_init(0,115200);

	PacketHandler_initialize(&packet_handler);
	PacketHandler_installPacket(&packet_handler, &test_ops);
	int global_seq = 0;



	while (1)
	{
		flushInputBuffers();
		test.header.seq = global_seq;
		++global_seq;
		
		if (test_buffer.prova == 1) 
		{
		DigIO_setDirection(10, 1);
		DigIO_setValue(10, 1);
		}

		PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &test);
		delayMs(10);
		flushOutputBuffers();
	}


}
