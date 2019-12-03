#include <string.h>
#include "smarthouse_host_globals.h"

int run=1;

TestConfigPacket test_config= {
	{
		.type=TEST_CONFIG_PACKET_ID,
		.size=sizeof (TestConfigPacket),
		.seq=0
	},
	.prova=0
}; 

TestStatusPacket test_status = {
	{
		.type=TEST_STATUS_PACKET_ID,
		.size=sizeof(TestStatusPacket),
		.seq=0
	},
	.sync=0
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
	.intensity=0
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
	.intensity=0,
	.inputs=0
};

AnalogConfigPacket analog_config=
{
	{
		.type=ANALOG_CONFIG_PACKET_ID,
		.size=sizeof(AnalogConfigPacket),
		.seq=0
	},
	.pin_analog=0,
	.samples=0
};

AnalogStatusPacket analog_status=
{
	{
		.type=ANALOG_STATUS_PACKET_ID,
		.size=sizeof(AnalogStatusPacket),
		.seq=0
	},
	.pin_analog=0,
	.samples=0,
	.result= {0,0,0,0,0,0,0,0,0,0}
};
