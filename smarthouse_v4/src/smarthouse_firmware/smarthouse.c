#include <stdio.h>
#include <string.h>
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

TestConfigPacket test_config = 
{
	{
		.type=TEST_CONFIG_PACKET_ID,
		.size=sizeof (TestConfigPacket),
		.seq=0
	},
	.prova=0

}; 	//il campo "prova = 0";;
TestStatusPacket test_config_buffer;

#define ACK 0x99
TestStatusPacket test_status = {
	{
		.type=TEST_STATUS_PACKET_ID,
		.size=sizeof(TestStatusPacket),
		.seq=0
	},
	.ack=ACK

};
TestStatusPacket test_status_buffer;

/*DigitalConfigPacket digital_config =
{
	{
		DIGITAL_CONFIG_PACKET_ID,
		sizeof(DigitalConfigPacket),
		0
	},
	0,
	0,
	0,
	0
};

DigitalConfigPacket digital_config_buffer;
*/
DigitalStatusPacket digital_status=
{
	{
		.type=DIGITAL_STATUS_PACKET_ID,
		.size=sizeof(DigitalStatusPacket),
		.seq=0
	},
	.status_digital=0
};

DigitalStatusPacket digital_status_buffer;

PacketHeader* firmware_initializeBuffer(PacketType type, PacketSize size, void* args __attribute__((unused))) 
{
	if (type==TEST_CONFIG_PACKET_ID && size==sizeof(TestConfigPacket))
	{	return (PacketHeader*) &test_config_buffer;	}
	else if(type==TEST_STATUS_PACKET_ID && size==sizeof(TestStatusPacket))
	{	return (PacketHeader*) &test_status_buffer;	}
/*	else if (type==DIGITAL_CONFIG_PACKET_ID && size==sizeof(DigitalConfigPacket))
	{	return (PacketHeader*) &digital_config_buffer;}
*/	else if (type== DIGITAL_STATUS_PACKET_ID && size==sizeof(DigitalStatusPacket))
	{	return (PacketHeader*) &digital_status_buffer;}
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
PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &digital_status);
			break;
		case TEST_STATUS_PACKET_ID:
			memcpy(&test_status, header, header->size);
			break;
/*		case DIGITAL_CONFIG_PACKET_ID:
			memcpy(&digital_config, header, header->size);
			if(digital_config.set_digital==1)
			{
				DigIO_setDirection(10, 1);
				DigIO_setValue(10, 1);
			}
			PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &test_status);
			break;
*/		case DIGITAL_STATUS_PACKET_ID:
			memcpy(&digital_status, header, header->size);
			break;
		default:
			break;
	}
	sync=1;
	delayMs(10);
	flushOutputBuffers();
	return Success;
}
/*
PacketHeader* config_firmware_initializeBuffer (PacketType type,
				       PacketSize size,
				       void* args __attribute__((unused))) {
	if(type!= TEST_CONFIG_PACKET_ID || size != sizeof(TestConfigPacket))
	{return 0;}
	return (PacketHeader*) &test_config_buffer;
}

PacketStatus config_firmware_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
	memcpy(&test_config, header, header->size);
PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &test_status);
	return Success;
}
*/
PacketOperations test_config_ops = {
	1,	//TEST_CONFIG_PACKET_ID,
	sizeof(TestConfigPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};
/*
PacketHeader* status_firmware_initializeBuffer (PacketType type,
				       PacketSize size,
				       void* args __attribute__((unused))) {
	if(type!= TEST_STATUS_PACKET_ID || size != sizeof(TestStatusPacket))
	{return 0;}
	return (PacketHeader*) &test_status_buffer;
}

PacketStatus status_firmware_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
	memcpy(&test_status, header, header->size);
	return Success;
}
*/
PacketOperations test_status_ops = {
	2,	//TEST_STATUS_PACKET_ID,
	sizeof(TestStatusPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};	

/*PacketOperations digital_config_ops = {
	DIGITAL_CONFIG_PACKET_ID,
	sizeof(DigitalConfigPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};
*/
PacketOperations digital_status_ops = {
	3,	//DIGITAL_STATUS_PACKET_ID,
	sizeof(DigitalStatusPacket),
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
//	PacketHandler_installPacket(&packet_handler, &digital_config_ops);
	PacketHandler_installPacket(&packet_handler, &digital_status_ops);	
	int global_seq = 0;
	sync=0;
	while (1)
	{
		flushInputBuffers();
		test_config.header.seq = global_seq;
		++global_seq;
		if(sync==0)
		{
			PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &test_status);
			delayMs(10);
			flushOutputBuffers();
		}
	}
	
}
