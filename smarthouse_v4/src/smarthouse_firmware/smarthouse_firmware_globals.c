#include <string.h>
#include "smarthouse_firmware_globals.h"

TestConfigPacket test_config= {
	{
		.type=TEST_CONFIG_PACKET_ID,
		.size=sizeof (TestConfigPacket),
		.seq=0
	},
	.prova=0
}; 

#define ACK 0x99
TestStatusPacket test_status = {
	{
		.type=TEST_STATUS_PACKET_ID,
		.size=sizeof(TestStatusPacket),
		.seq=0
	},
	.ack=ACK
};

DigitalConfigPacket digital_config =
{
	{
		.type=DIGITAL_CONFIG_PACKET_ID,
		.size=sizeof(DigitalConfigPacket),
		.seq=0
	},
	.pin_digital=0,
	.set_digital=0,
	.intensity=255,
	.inputs=0
};

DigitalStatusPacket digital_status=
{
	{
		.type=DIGITAL_STATUS_PACKET_ID,
		.size=sizeof(DigitalStatusPacket),
		.seq=0
	},
	.pin_digital=0,
	.set_digital=0,
	.intensity=255,
};
