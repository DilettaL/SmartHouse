#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "serial_linux.h"
#include "packet_handler.h"
#include "smarthouse_packets.h"

struct UART* uart;
PacketHandler packet_handler;

TestPacket test= { {TEST_PACKET_ID, sizeof (TestPacket), 0 }, 0}; 
TestPacket test_buffer;

PacketHeader* test_host_initializeBuffer(PacketType type,
				       PacketSize size,
				       void* args __attribute__((unused))) {
	if (type!=TEST_PACKET_ID || size!=sizeof(TestPacket))
		return 0;
	return (PacketHeader*) &test_buffer;
}

PacketStatus test_host_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
	memcpy(&test, header, header->size);
	printf("HOST: type %d\tValoreprova%d\n", header->type, test.prova);
	fflush(stdout);
	PacketHandler_sendPacket(&packet_handler, (PacketHeader*)&test);
	return Success;
}



PacketOperations test_ops = {
	1,
	sizeof(TestPacket),
	test_host_initializeBuffer,
	0,
	test_host_onReceive,
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
	PacketHandler_installPacket(&packet_handler, &test_ops);

	test.prova=0; 
volatile int packet_complete =1;
	for (int i=0; i<100; ++i)
	{
		while ( packet_complete ==0) 
		{
			uint8_t c;
			int n=read (fd, &c, 1);
			if (n) 
			{
				PacketStatus status = PacketHandler_rxByte(&packet_handler, c);
				if (status<0)
					printf("%d",status);
				fflush(stdout);
				packet_complete = (status==SyncChecksum);
			}
		}
		while(packet_handler.tx_size)
		{
			uint8_t c=PacketHandler_txByte(&packet_handler);
			ssize_t res = write(fd,&c,1);
packet_complete=0;
		usleep(10);
		}
	}
return 0;
}



