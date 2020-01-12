#include <string.h>
#include <stdio.h>
#include "smarthouse_host_globals.h"

void printBanner(void)
{
	printf ("Smarthouse\nusage:\n$>Smarthouse	...\nto choice operation insert one of this commands(then choice the pin and other settings):\n$>Smarthouse	ledOn\n$>Smarthouse	dimmer\n$>Smarthouse	digital_input\n$>Smarthouse	ledOff\n$>Smarthouse	adc\nto request a status packet insert(then choice packet type):\n$>Smarthouse	request\nto access to eeprom insert(then choice pin and packet type):\n$>Smarthouse	save\nor\n$>Smarthouse	load\nto exit insert:\n$>Smarthouse	quit");
}


int run=1;
PacketHeader *pointer_packet=(PacketHeader*)&test_config;

TestConfigPacket test_config=
{
	.header.type=TEST_CONFIG_PACKET_ID,
	.header.size=sizeof (TestConfigPacket),
	.header.seq=0,
	.prova=0
}; 

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

NameSet name =
{
	.arduino={"Smarthouse"},//S',0,0,0,0,0,0,0,0,0},
	.pt_pin = &name.digital_0[0],
	.digital_0={"digital_0"},
	.digital_1={"digital_1"},
	.digital_2={"digital_2"},
	.digital_3={"digital_3"},
	.digital_4={"digital_4"},
	.digital_5={"digital_5"},
	.digital_6={"digital_6"},
	.digital_7={"digital_7"},
	.digital_8={"digital_8"},
	.digital_9={"digital_9"},
	.digital_10={"digital_10"},
	.digital_11={"digital_11"},
	.digital_12={"digital_12"},
	.analog_0={"analog_0"},//14
	.analog_1={"analog_1"},
	.analog_2={"analog_2"},
	.analog_3={"analog_3"},
	.analog_4={"analog_4"},
	.analog_5={"analog_5"},
	.analog_6={"analog_6"},
	.analog_7={"analog_7"},
	.analog_8={"analog_8"},
	.analog_9={"analog_9"},
	.analog_10={"analog_10"},
	.analog_11={"analog_11"},
	.analog_12={"analog_12"},
	.analog_13={"analog_13"},
	.analog_14={"analog_14"},
};
