//Quanto sei bella Roma
//Generale dietro la collina
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "serial_linux.h"
#include "smarthouse_host_globals.h"
#include "packet_handler.h"
#include "smarthouse_packets.h"

struct UART* uart;
PacketHandler packet_handler;

//variables for initializeBuffer
TestAck test_ack_buffer;
/*TestAck test_ack = {
	{
		.type=TEST_ACK_ID,
		.size=sizeof(TestAck),
		.seq=0
	},
	.feedback_seq=0
};
*/
TestConfig test_config_buffer;
/*TestConfig test_config= {
	{
		.type=TEST_CONFIG_ID,
		.size=sizeof (TestConfig),
		.seq=0
	},
	.prova=0
};*/ 

TestStatus test_status_buffer;
/*TestStatus test_status = {
	{
		.type=TEST_STATUS_ID,
		.size=sizeof(TestStatus),
		.seq=0
	},
	.prova=0
};*/
int i;

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


//////START generic _onReceive: with dedicate ops
PacketStatus host_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
	switch (header->type)
	{
		case TEST_ACK_ID:
			++header->seq;
			memcpy(&test_ack, header, header->size);
			printf ("Val ACK=%d\n",test_ack.feedback_seq);
			break;
		case TEST_CONFIG_ID:	
			++header->seq;
			memcpy(&test_config, header, header->size);
			return Success;
			break;
		case TEST_STATUS_ID:
			++header->seq;
			PacketIndexed* p_idx=(PacketIndexed*)header;
			memcpy(&test_status+(header->size)*(p_idx->index), header, header->size);
			printf ("test_status[].prova=%d\n",test_status[p_idx->index].prova);
//i=998;
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
//////END generic _onReceive

/*
PacketStatus ack_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
	memcpy(&test_ack, header, header->size);
	printf ("Val ACK=%d\n",test_ack.feedback_seq);
	return Success;
}

PacketStatus config_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
	memcpy(&test_config, header, header->size);
	return Success;
}

PacketStatus status_onReceive(PacketHeader* header,
			       void* args __attribute__((unused))) {
	++header->seq;
	memcpy(&test_status, header, header->size);
	printf ("test_status.prova=%d\n",test_status.prova);
i=1000;
	return Success;
}
PacketOperations test_ack_ops = {
	TEST_ACK_ID,
	sizeof(TestAck),
	host_initializeBuffer,
	0,
	ack_onReceive,
	0
};

PacketOperations test_config_ops = {
	TEST_CONFIG_ID,
	sizeof(TestConfig),
	host_initializeBuffer,
	0,
	config_onReceive,
	0
};

PacketOperations test_status_ops = {
	TEST_STATUS_ID,
	sizeof(TestStatus),
	host_initializeBuffer,
	0,
	status_onReceive,
	0
};
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
	PacketHandler_installPacket(&packet_handler, &test_ack_ops);
	PacketHandler_installPacket(&packet_handler, &test_config_ops);
	PacketHandler_installPacket(&packet_handler, &test_status_ops);
	
	for ( i = 0; i < 1000; i++ )
	{
	test_config.prova=5;
printf("%d] ",i);
//Invio: void send (void)
		PacketHandler_sendPacket(&packet_handler, (PacketHeader*)&test_config);
		while(packet_handler.tx_size)
		{
			uint8_t c=PacketHandler_txByte(&packet_handler);
			ssize_t res = write(fd,&c,1);
			usleep(10);
		}
//Ricezione:
		volatile int packet_complete =0;
		while ( !packet_complete ) 
		{
			uint8_t c;
			int n=read (fd, &c, 1);
printf("c=%x ", c);
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
printf("\n");
	}
	
	return 0;
}
