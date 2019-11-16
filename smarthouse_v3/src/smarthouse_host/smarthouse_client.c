#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "smarthouse_client.h"
#include "serial_linux.h"

typedef struct SmarthouseClient {
	PacketHandler packet_handler;
	uint16_t global_seq;
  
	//these are the system variables, updated by the serial communiction
//  ResponsePacket response;
//  StringMessagePacket message;
//  EndEpochPacket end_epoch;
//	SystemStatusPacket system_status;
	SystemParamPacket system_params;
//	DigitalParamPacket digital_params[DIGITAL_MAX];
//	AnalogParamPacket analog_params[ANALOG_MAX];
	TestPacket test;

	// file descriptor of the serial port
	int fd;
	uint8_t packet_buffer[PACKET_SIZE_MAX];

	//sanity check on transmission
	PacketSize packet_sizes[PACKET_TYPE_MAX];
	pthread_mutex_t write_mutex;
	pthread_mutex_t read_mutex;

	// number of digital pins declared by the platform
	int num_digital;
	// number of analog pins declared by the platform
	int num_analog;

	int rx_bytes;
	int tx_bytes;
} SmarthouseClient;


static PacketStatus _installPacketOp(SmarthouseClient* cl, void* dest, PacketType type, PacketSize size, int indexed)
{
	//alloco una packetoperations per ogni pacchetto, definendone tipo e dimensione
	PacketOperations* ops=(PacketOperations*)malloc(sizeof(PacketOperations));
	ops->type=type;
	ops->size=size;
//	ops->initialize_buffer_fn=_initializeBuffer;
	ops->initialize_buffer_args=cl; //it isn't only argument of function
/*	if (indexed!=0)// analogo if(indexed)
	{	ops->on_receive_fn=_copyToIndexedBuffer;	}
	else //else if (indexed==0)
	{	ops->on_receive_fn=_copyToBuffer;	}
*/	ops->on_receive_args=dest;	//packet installation with handler
	PacketStatus install_result =PacketHandler_installPacket(&cl->packet_handler, ops);
	if(install_result!=Success)
	{
		printf("error in installing ops");
		exit(0);
		assert(0);
	}
	return install_result;
}


struct SmarthouseClient* SmarthouseClient_init(const char* device, uint32_t baudrate)
{
//Configure serial port
int fd=serial_open(device);
  if(fd<0)
    return 0;
  if (serial_set_interface_attribs(fd, baudrate, 0) <0)
    return 0;
  serial_set_blocking(fd, 1); 
  if  (! fd)
    return 0;
  
	//Set memory part for client and the packets
	SmarthouseClient* cl=(SmarthouseClient*) malloc(sizeof(SmarthouseClient));
	cl->global_seq=0;
	cl->fd=fd;
	cl->num_digital=0;
	cl->num_analog=0;
	cl->rx_bytes=0;
	cl->tx_bytes=0;
//***************INIZIO: INIZIALIZZAZIONE PACCHETTO DI PROVA
	TestPacket test=
	{
		{
			.type=TEST_PACKET_ID,
			.size=sizeof(TestPacket),
      			.seq=0
    		},
		.prova=1
	};
	// initializes the packet system
	PacketHandler_initialize(&cl->packet_handler);
	//packets installation on host
	_installPacketOp(cl, &system_params, SYSTEM_PARAM_PACKET_ID, sizeof(cl->system_params), 0);
//Installazione della prova
	_installPacketOp(cl, &test, TEST_PACKET_ID, sizeof(cl->test), 0);
	memset(&cl->packet_sizes, 0, sizeof(cl->packet_sizes));
	cl->packet_sizes[SYSTEM_PARAM_PACKET_ID]=sizeof(SystemParamPacket);
//Prova
	cl->packet_sizes[TEST_PACKET_ID]=sizeof(TestPacket);
	return cl;	
}
/*********************************TRASMISSIONE***********************************************/

static PacketStatus _sendPacket(SmarthouseClient* cl, PacketHeader* p)
{
	++cl->global_seq;
	PacketType type=p->type;
	if(type>=PACKET_TYPE_MAX)
	{	return UnknownType;	}
	PacketSize expected_size=cl->packet_sizes[type];
	if(! expected_size)
	{	return UnknownType;	}
	if(p->size!=expected_size)
	{	return InvalidSize;	}
	p->seq=cl->global_seq;
	return PacketHandler_sendPacket(&cl->packet_handler, p);
}

static void _flushBuffer(SmarthouseClient* cl)
{
	while(cl->packet_handler.tx_size)
	{
		uint8_t c=PacketHandler_txByte(&cl->packet_handler);
		ssize_t res = write(cl->fd,&c,1);
		cl->tx_bytes+=res;
	}
}

PacketStatus SmarthouseClient_sendPacket(SmarthouseClient* cl, PacketHeader* p)//int time_out);
{
	PacketStatus send_result;
	//we do only operations and nobody else can read/write packet
	pthread_mutex_lock(&cl->write_mutex);
	pthread_mutex_lock(&cl->read_mutex); 
	send_result=_sendPacket(cl,p);
  	if(send_result!=Success)
	{
		printf("Error of transmission\n");
		//goto safe_exit;
	}
	_flushBuffer(cl);
	pthread_mutex_unlock(&cl->read_mutex);
	pthread_mutex_unlock(&cl->write_mutex);
	return send_result;	
}