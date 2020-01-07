#include <string.h>
#include "smarthouse_firmware_globals.h"

TestConfigPacket test_config=
{
	.header.type=TEST_CONFIG_PACKET_ID,
	.header.size=sizeof (TestConfigPacket),
	.header.seq=0,
	.prova=0
}; 

/*TestStatusPacket test_status=
{
	.header.type=TEST_STATUS_PACKET_ID,
	.header.size=sizeof(TestStatusPacket),
	.header.seq=0,
	.sync=0
};*/

DigitalConfigPacket digital_config=
{
	.header.type=DIGITAL_CONFIG_PACKET_ID,
	.header.size=sizeof(DigitalConfigPacket),
	.header.seq=0,
	.pin_digital=0,
	.set_digital=0,
	.intensity=0
};

DigitalStatusPacket digital_status[NUM_DIGITAL]=
{
	{//Pin_digital 0
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=0
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 1
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=1
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 2
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=2
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 3
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=3
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 4
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=4
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 5
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=5
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 6
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=6
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 7
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=7
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 8
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=8
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 9
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=9
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 10
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=10
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 11
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=11
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
	{//Pin_digital 12
		{
			{
				.type=DIGITAL_STATUS_PACKET_ID,
				.size=sizeof(DigitalStatusPacket),
				.seq=0
			},
		.index=12
		},
		.pin_digital=0,
		.set_digital=0,
		.intensity=0,
		.inputs=0
	},
};

AnalogConfigPacket analog_config=
{
	.header.type=ANALOG_CONFIG_PACKET_ID,
	.header.size=sizeof(AnalogConfigPacket),
	.header.seq=0,
	.pin_analog=0,
	.samples=0
};

AnalogStatusPacket analog_status[NUM_ANALOG]=
{
	{//Pin_analog 0
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=0
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 1
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=1
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 2
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=2
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 3
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=3
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 4
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=4
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 5
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=5
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 6
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=6
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 7
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=7
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 8
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=8
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 9
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=9
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 10
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=10
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 11
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=11
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 12
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=12
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 13
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=13
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	},
	{//Pin_analog 14
		{
			{
				.type=ANALOG_STATUS_PACKET_ID,
				.size=sizeof(AnalogStatusPacket),
				.seq=0
			},
		.index=14
		},
		.pin_analog=0,
		.samples=0,
		.result= {0,0,0,0,0,0,0,0,0,0}
	}
};

EepromPacket eeprom =
{
	.header.type=EEPROM_PACKET_ID,
	.header.size=sizeof(EepromPacket),
	.header.seq=0,
	.action=1,
	.type_pin=0,
	.pin=0
};
