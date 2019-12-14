#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <pthread.h>
#include <stdbool.h>
#include "serial_linux.h"
#include "smarthouse_host_globals.h"
#include "smarthouse_shell.h"
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
int busy=0;
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
void printPacket_digital(uint8_t pin)
{
	printf("Digital Mode:\t");
	if(digital_status[pin].set_digital==0) {printf("Led off\n");}
	else if(digital_status[pin].set_digital==1) {printf("Led on\n");}
	else if(digital_status[pin].set_digital==2) {printf("Dimmer\n"); printf("Intensity=%d\n", digital_status[pin].intensity);}
	else if(digital_status[pin].set_digital==3) {printf("Input digital\n"); printf("Value=%d\n", digital_status[pin].inputs);}
	else {printf("Error, mode not");}
	printf("Pin Digital:%d\n", digital_status[pin].pin_digital);
	printf("Smarthouse> ");
	busy=1;
}

void printPacket_analog(uint8_t pin)
{
	printf("Analog Mode:\n");
	printf("Pin Analog:%d\n", analog_status[pin].pin_analog);	
	for(int i=0; i<analog_status[pin].samples; i++)
	{
		printf("Sample[%d] = %d\n", i,analog_status[pin].result[i]);
	}
	printf("Smarthouse> ");
}
PacketStatus host_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
	PacketIndexed *idx_p=(PacketHeader*)header;
	switch (header->type)
	{ 
		case TEST_CONFIG_PACKET_ID:
			break;
		case TEST_STATUS_PACKET_ID:	
			break;
		case DIGITAL_CONFIG_PACKET_ID:
			break;
		case DIGITAL_STATUS_PACKET_ID:
			memcpy(&digital_status[idx_p->index], header, header->size);
			printPacket_digital(idx_p->index);
			pointer_packet=(PacketHeader*)&test_config;
			break;
		case ANALOG_CONFIG_PACKET_ID:
			break;
		case ANALOG_STATUS_PACKET_ID:
			memcpy(&analog_status[idx_p->index], header, header->size);
			printPacket_analog(idx_p->index);
			pointer_packet=(PacketHeader*)&test_config;
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

void* keyboardFn()
{
	while(run)
	{
			while(lock_k!=1)
			{
			printf("Smarthouse> ");
			char *buffer = readline("");
//			char *buffer = readline("Smarthouse> ");
			if (buffer)
			{
				executeCommand(buffer);
				if (*buffer)
				{//	add_history(buffer);
					free(buffer);
				}
				else
				{	run=0;	}
			}
			busy=0;
			lock_k=1;
			lock_s=0;
			}			
	}
	return 0;
}


void* serialFn()
{
	int fd=serial_open("/dev/ttyACM0");
	if(fd<0)
		return 0;
	if (serial_set_interface_attribs(fd, 115200, 0) <0)
		return 0;
	serial_set_blocking(fd, 1); 
	if  (! fd)
	{	return 0;	}
	while(run)
	{
		while(lock_s!=0);
		PacketHandler_sendPacket(&packet_handler, pointer_packet);
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
		if(busy==1)
		{
			lock_k=0;
			lock_s=1;
		}
	}
	return 0;
}

int main (int argc, char **argv)
{
	lock_s=1;
	PacketHandler_initialize(&packet_handler);
	PacketHandler_installPacket(&packet_handler, &test_config_ops);
	PacketHandler_installPacket(&packet_handler, &test_status_ops);
	PacketHandler_installPacket(&packet_handler, &digital_config_ops);
	PacketHandler_installPacket(&packet_handler, &digital_status_ops);
	PacketHandler_installPacket(&packet_handler, &analog_config_ops);
	PacketHandler_installPacket(&packet_handler, &analog_status_ops);
	pointer_packet=(PacketHeader*)&test_config;
	printf("Shell Start\n");
//Threads
	pthread_t serial, keyboard;
	pthread_create (&keyboard, NULL, keyboardFn, NULL);
	pthread_create (&serial, NULL, serialFn, NULL);
//Wait threads end
	pthread_join(keyboard, NULL);
	pthread_join(serial, NULL);
	return 0;
}
