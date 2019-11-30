#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "serial_linux.h"
#include "packet_handler.h"
#include "smarthouse_packets.h"

struct UART* uart;
PacketHandler packet_handler;

TestConfigPacket test_config= { {TEST_CONFIG_PACKET_ID, sizeof (TestConfigPacket), 0 }, 0}; 
TestConfigPacket test_config_buffer;

#define ACK 0x99
TestStatusPacket test_status = { {TEST_STATUS_PACKET_ID, sizeof(TestStatusPacket), 0}, ACK};
TestStatusPacket test_status_buffer;

DigitalConfigPacket digital_config =
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

DigitalStatusPacket digital_status=
{
	{
		DIGITAL_STATUS_PACKET_ID,
		sizeof(DigitalStatusPacket),
		0
	},
	0
};

DigitalStatusPacket digital_status_buffer;

PacketHeader* host_initializeBuffer(PacketType type,
				       PacketSize size,
				       void* args __attribute__((unused))) {
	if (type==TEST_CONFIG_PACKET_ID && size==sizeof(TestConfigPacket))
	{	return (PacketHeader*) &test_config_buffer;}
	else if (type==TEST_STATUS_PACKET_ID && size == sizeof(TestStatusPacket))
	{	return (PacketHeader*) &test_status_buffer;}
	else if (type==DIGITAL_CONFIG_PACKET_ID && size==sizeof(DigitalConfigPacket))
	{	return (PacketHeader*) &digital_config_buffer;}
	else if (type== DIGITAL_STATUS_PACKET_ID && size==sizeof(DigitalStatusPacket))
	{	return (PacketHeader*) &digital_status_buffer;}
	else
	{
		printf("Errore, nessun tipo di pacchetto è stato ricevuto\n");
		return 0;
	}
}

PacketStatus host_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
/*DeBUG*/printf("okokok\n");
	switch (header->type)
	{
		case TEST_CONFIG_PACKET_ID:
			memcpy(&test_config, header, header->size);
			break;
		case TEST_STATUS_PACKET_ID:	
			memcpy(&test_status, header, header->size);
			break;
		case DIGITAL_CONFIG_PACKET_ID:
			memcpy(&digital_config, header, header->size);
			break;
		case DIGITAL_STATUS_PACKET_ID:
			memcpy(&digital_status, header, header->size);
			break;
		default:
			break;
	}
/*DEBUG*/		printf("Host Receive: %d\n", test_status.ack);
	return Success;
}
PacketOperations test_config_ops = {
	TEST_CONFIG_PACKET_ID,
	sizeof(TestConfigPacket),
	host_initializeBuffer,
	0,
	host_onReceive,
	0
};

PacketOperations test_status_ops = {
	TEST_STATUS_PACKET_ID,
	sizeof(TestStatusPacket),
	host_initializeBuffer,
	0,
	host_onReceive,
	0
};

PacketOperations digital_config_ops = {
	DIGITAL_CONFIG_PACKET_ID,
	sizeof(DigitalConfigPacket),
	host_initializeBuffer,
	0,
	host_onReceive,
	0
};

PacketOperations digital_status_ops = {
	DIGITAL_STATUS_PACKET_ID,
	sizeof(DigitalStatusPacket),
	host_initializeBuffer,
	0,
	host_onReceive,
	0
};

int main (int argc, char **argv)
{
	assert(argc>1);
	int fd=serial_open(argv[1]);
	if(fd<0)
		return 0;
	if (serial_set_interface_attribs(fd, 115200, 0) <0)
		return 0;
	serial_set_blocking(fd, 1); 
	if  (! fd)
		return 0;
	PacketHandler_initialize(&packet_handler);
	PacketHandler_installPacket(&packet_handler, &test_config_ops);
	PacketHandler_installPacket(&packet_handler, &test_status_ops);
	PacketHandler_installPacket(&packet_handler, &digital_config_ops);
	PacketHandler_installPacket(&packet_handler, &digital_status_ops);
	digital_config.set_digital=1;
	for (int i=0; i<1000; ++i)
	{
		PacketHandler_sendPacket(&packet_handler, (PacketHeader*)&digital_config);
/*DEBUG*/	printf("%d]\tHost Transmission (mi aspetto 1): test-> %d\n", i, digital_config.set_digital);
		while(packet_handler.tx_size)
		{
			uint8_t c=PacketHandler_txByte(&packet_handler);
			ssize_t res = write(fd,&c,1);
			usleep(10);
		}
		volatile int packet_complete =0;
		while ( !packet_complete ) 
		{
			uint8_t c;
			int n=read (fd, &c, 1);
			if (n) 
			{
				PacketStatus status = PacketHandler_rxByte(&packet_handler, c);
				if (status<0)
				{	printf("%d",status);
					fflush(stdout);
				}
				packet_complete = (status==SyncChecksum);
			}
		}
	}	
	return 0;
}
