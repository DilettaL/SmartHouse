#include <stdio.h>
#include <string.h>
#include "smarthouse_firmware_globals.h"
//#include "smarthouse_functions.h"
#include "packet_handler.h"
#include "smarthouse_packets.h"
#include "digio.h"
#include "uart.h"
#include "delay.h"

uint8_t sync;
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

//variables for initializeBuffer
TestAck test_ack_buffer;
TestConfig test_config_buffer;
TestStatus test_status_buffer;

PacketHeader* host_initializeBuffer(PacketType type,
				       PacketSize size,
				       void* args __attribute__((unused))) {
	if (type==TEST_ACK_ID && size==sizeof(TestAck))
	{	return (PacketHeader*) &test_ack_buffer;}
	else if (type==TEST_CONFIG_ID && size == sizeof(TestConfig))
	{	return (PacketHeader*) &test_config_buffer;}
	else if (type==TEST_STATUS_ID && size==sizeof(TestStatus))
	{	return (PacketHeader*) &test_status_buffer;}

	else
	{
		printf("Errore, nessun tipo di pacchetto è stato ricevuto\n");
		return 0;
	}
}


PacketStatus host_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
	switch (header->type)
	{
		case TEST_ACK_ID:
///////
			break;
		case TEST_CONFIG_ID:	
			memcpy(&test_config, header, header->size);
PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &test_status );

DigIO_setDirection(10, 1);
DigIO_setValue(10, 1);
			break;
		case TEST_STATUS_ID:
//////
			break;
		default:
			break;
	}
	return Success;
}


PacketOperations test_ack_ops = {
	TEST_ACK_ID,
	sizeof(TestAck),
	host_initializeBuffer,
	0,
	host_onReceive,
	0
};

PacketOperations test_config_ops = {
	TEST_CONFIG_ID,
	sizeof(TestConfig),
	host_initializeBuffer,
	0,
	host_onReceive,
	0
};

PacketOperations test_status_ops = {
	TEST_STATUS_ID,
	sizeof(TestStatus),
	host_initializeBuffer,
	0,
	host_onReceive,
	0
};

int main (int argc, char** argv)
{	
	uart = UART_init(0,115200);
	DigIO_init();
	PacketHandler_initialize(&packet_handler);
	PacketHandler_installPacket(&packet_handler, &test_ack_ops);
	PacketHandler_installPacket(&packet_handler, &test_config_ops);
	PacketHandler_installPacket(&packet_handler, &test_status_ops);	

	int global_seq = 0;
	delayMs(500);
	while (1)
	{
		flushInputBuffers();
		test_ack.header.seq = global_seq;
		++global_seq;

		PacketHandler_sendPacket(&packet_handler, (PacketHeader*)&test_ack);
		delayMs(10);
		flushOutputBuffers();
	}	
}
