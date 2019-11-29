#include <stdio.h>
#include <string.h>
#include "packet_handler.h"
#include "smarthouse_packets.h"
#include "digio.h"
#include "uart.h"
#include "delay.h"

static struct UART* uart;
static PacketHandler packet_handler;

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

TestConfigPacket test_config = { {TEST_CONFIG_PACKET_ID, sizeof(TestConfigPacket), 0}, 0 }; 	//il campo "prova = 0";;
TestStatusPacket test_config_buffer;

#define ACK 0x99
TestStatusPacket test_status = { {TEST_STATUS_PACKET_ID, sizeof(TestStatusPacket), 0}, ACK};
TestStatusPacket test_status_buffer;

PacketHeader* firmware_initializeBuffer(PacketType type, PacketSize size, void* args __attribute__((unused))) 
{
	if (type==TEST_CONFIG_PACKET_ID && size==sizeof(TestConfigPacket))
	{	return (PacketHeader*) &test_config_buffer;	}
	else if(type==TEST_STATUS_PACKET_ID && size==sizeof(TestStatusPacket))
	{	return (PacketHeader*) &test_status_buffer;	}
	else
	{	return 0; }
}

PacketStatus firmware_onReceive(PacketHeader* header, void* args __attribute__((unused))) 
{
	++header->seq;
	switch (header->type)
	{
		case TEST_CONFIG_PACKET_ID:
			memcpy(&test_config, header, header->size);
/*DEBUG*/		PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &test_status);
			break;
		case TEST_STATUS_PACKET_ID:
			memcpy(&test_status, header, header->size);
			break;
		default:
			break;
	}
	delayMs(10);
	flushOutputBuffers();
	return Success;
}
PacketOperations test_config_ops = {
	1,
	sizeof(TestConfigPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};

PacketOperations test_status_ops = {
	2,
	sizeof(TestStatusPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};	

int main (int argc, char** argv)
{
	DigIO_init();
	uart = UART_init(0,115200);
	PacketHandler_initialize(&packet_handler);
	PacketHandler_installPacket(&packet_handler, &test_config_ops);
	PacketHandler_installPacket(&packet_handler, &test_status_ops);
	int global_seq = 0;
	while (1)
	{
		flushInputBuffers();
		test_config.header.seq = global_seq;
		++global_seq;
		PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &test_status);
		delayMs(10);
		flushOutputBuffers();
	}
	
}
