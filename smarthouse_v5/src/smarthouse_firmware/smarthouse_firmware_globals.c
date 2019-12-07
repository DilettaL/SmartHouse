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

TestStatusPacket test_status = {
	{
		.type=TEST_STATUS_PACKET_ID,
		.size=sizeof(TestStatusPacket),
		.seq=0
	},
	.sync=0
};

DigitalConfigPacket digital_config[NUM_DIGITAL] =
{
	{//pin_digital 0
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=0
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 1
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=1
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 2
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=2
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 3
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=3
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 4
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=4
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 5
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=5
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 6
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=6
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 7
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=7
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 8
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=8
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 9
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=9
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 10
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=10
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 11
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=11
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	},
	{//pin_digital 12
		{
			{
				.type=DIGITAL_CONFIG_PACKET_ID,
				.size=sizeof(DigitalConfigPacket),
				.seq=0
			},
			.index=12
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0
	}
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
