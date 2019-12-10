#include <string.h>
#include "smarthouse_firmware_globals.h"

TestAck test_ack = {
	{
		.type=TEST_ACK_ID,
		.size=sizeof(TestAck),
		.seq=0
	},
	.feedback_seq=0x88
};


TestConfig test_config= {
	{
		.type=TEST_CONFIG_ID,
		.size=sizeof (TestConfig),
		.seq=0
	},
	.prova=0
}; 

TestStatus test_status= 
{
	{
		.type=TEST_STATUS_ID,
		.size=sizeof(TestStatus),
		.seq=0
	},
	.prova=1
};

