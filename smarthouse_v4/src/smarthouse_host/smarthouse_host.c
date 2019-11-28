#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "serial_linux.h"
#include "packet_handler.h"
#include "smarthouse_packets.h"

///***
#include <pthread.h>
#include <stdlib.h>
///***

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
	printf("Host On receive (mi aspetto 7): test-> %d\theader-> %d\n", test.prova, *((uint8_t*)header+4) );
	fflush(stdout);
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

///****
int fd;
void *listen_serial()
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
					printf("%d",status);
				fflush(stdout);
				packet_complete = (status==SyncChecksum);
			}
		}
	return (void*) 0;
}

///*****
int main (int argc, char **argv)
{
	assert(argc>1);
//****

int thread_exit;
pthread_t serial;
pthread_attr_t attr_serial;
pthread_attr_init(&attr_serial);
fd=serial_open(argv[1]);
	if(fd<0)
		return 0;
	if (serial_set_interface_attribs(fd, 115200, 0) <0)
		return 0;
	serial_set_blocking(fd, 1); 
	if  (! fd)
		return 0;
	

int control=pthread_create(&serial, &attr_serial, &listen_serial, NULL);
if (control)
{
    	printf("ERROR; return code from pthread_create()\n");
        exit(-1);
}
//****
	PacketHandler_initialize(&packet_handler);
	PacketHandler_installPacket(&packet_handler, &test_ops);

	test.prova=8; 
	for (int i=0; i<1000; ++i)
	{
/*		volatile int packet_complete =0;
		while ( !packet_complete ) 
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
*/

test.prova=8;
PacketHandler_sendPacket(&packet_handler, (PacketHeader*)&test);
printf("%d]\tHost Transmission (mi aspetto 8): test-> %d\n", i, test.prova);
		while(packet_handler.tx_size)
		{
			uint8_t c=PacketHandler_txByte(&packet_handler);
			ssize_t res = write(fd,&c,1);
		usleep(10);
		}
	//****
int count=0;
while(	( count = pthread_join(serial, (void*)&thread_exit) ) !=0 ){
	printf ("--count = %d\n", count);
}
//****
	}
pthread_attr_destroy(&attr_serial);	
	return 0;
}





