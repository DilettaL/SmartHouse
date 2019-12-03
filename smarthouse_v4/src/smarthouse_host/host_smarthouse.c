#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "serial_linux.h"
#include "smarthouse_host_globals.h"
#include "packet_handler.h"
#include "smarthouse_packets.h"


const char *banner[]={
	"Smarthouse",
	"usage:",
	"$>Smarthouse	...",
	"to choice operation insert one of this commands(then choice the pin and other settings):",
	"$>Smarthouse	ledOn",
	"$>Smarthouse	dimmer",
	"$>Smarthouse	digital input",
	"$>Smarthouse	ledOff",
	"$>Smarthouse	adc",
	"to request a status packet insert(then choice packet type):",
	"$>Smarthouse	request",
	"to exit insert:",
	"$>Smarthouse	quit"
};

void printBanner(void)
{
	const char*const* line=banner;
	while (*line)
	{
		printf("%s\n",*line);
		line++;
	}
}

struct UART* uart;
PacketHandler packet_handler;

//variables for initializeBuffer
TestConfigPacket test_config_buffer;
TestStatusPacket test_status_buffer;
DigitalConfigPacket digital_config_buffer;
DigitalStatusPacket digital_status_buffer;
AnalogConfigPacket analog_config_buffer;
AnalogStatusPacket analog_status_buffer;

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
	else if (type== ANALOG_CONFIG_PACKET_ID && size==sizeof(AnalogConfigPacket))
	{	return (PacketHeader*) &analog_config_buffer;}
	else if (type== ANALOG_STATUS_PACKET_ID && size==sizeof(AnalogStatusPacket))
	{	return (PacketHeader*) &analog_status_buffer;}	
	
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
		case TEST_CONFIG_PACKET_ID:
/*DEBUG*/printf("Errore\n");
			break;
		case TEST_STATUS_PACKET_ID:	
			memcpy(&test_status, header, header->size);
/*DEBUG	*/printf("Sync\n");
			break;
		case DIGITAL_CONFIG_PACKET_ID:
/*DEBUG*/printf("Errore\n");
			break;
		case DIGITAL_STATUS_PACKET_ID:
			memcpy(&digital_status, header, header->size);
/*DEBUG*/printf("RECEIVE: Acceso pin (aspetto 10) =%d\tSet_digital (aspetto1)=%d\tinput_digital=%d\n", digital_status.pin_digital, digital_status.set_digital, digital_status.inputs);
			break;
		case ANALOG_CONFIG_PACKET_ID:
/*DEBUG*/printf("Errore\n");
			break;
		case ANALOG_STATUS_PACKET_ID:
			memcpy(&analog_status, header, header->size);
/*DEBUG*/printf("RECEIVE: Pin: %d\tSamples:\n", analog_status.pin_analog);
/*DEBUG*/for(uint16_t i=0; i<analog_status.samples; i++)
	{
		printf("%hn\n", analog_status.result+i);
	}
			break;
		default:
			break;
	}
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

PacketOperations analog_config_ops = {
	ANALOG_CONFIG_PACKET_ID,
	sizeof(AnalogConfigPacket),
	host_initializeBuffer,
	0,
	host_onReceive,
	0
};

PacketOperations analog_status_ops = {
	ANALOG_STATUS_PACKET_ID,
	sizeof(AnalogStatusPacket),
	host_initializeBuffer,
	0,
	host_onReceive,
	0
};
/*
void readSerial(void)
{
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

void Smarthouse_sendPacket( (PacketHeader*) packet)
{
	PacketHandler_sendPacket(&packet_handler, &packet);	
	while(packet_handler.tx_size)
	{
		uint8_t c=PacketHandler_txByte(&packet_handler);
		ssize_t res = write(fd,&c,1);
		usleep(10);
	}
}
*/
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
	PacketHandler_installPacket(&packet_handler, &analog_config_ops);
	PacketHandler_installPacket(&packet_handler, &analog_status_ops);
	printf("Shell Start\n");	
	analog_config.pin_analog=3;
	analog_config.samples=10;
	for (int i=0; i<1000; ++i)
	{
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

		PacketHandler_sendPacket(&packet_handler, (PacketHeader*)&analog_config);	
printf("%d]\tHost Transmission Numero Pin:%d\n", i, analog_config.pin_analog);
		while(packet_handler.tx_size)
		{
			uint8_t c=PacketHandler_txByte(&packet_handler);
			ssize_t res = write(fd,&c,1);
			usleep(10);
		}
	}	
	return 0;
}
