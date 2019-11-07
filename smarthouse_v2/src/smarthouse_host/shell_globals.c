#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "shell_globals.h"

struct SmarthouseClient* client=0;
int run=1;

//*****PROVA
PacketTest test = {
	.header.type=TEST_PACKET_ID,
	.header.size=sizeof(PacketTest)
};
//*****PROVA

SystemStatusPacket system_status={
  .header.type=SYSTEM_STATUS_PACKET_ID,
  .header.size=sizeof(SystemStatusPacket)
};

SystemParamPacket system_params={
  .header.type=SYSTEM_PARAM_PACKET_ID,
  .header.size=sizeof(SystemParamPacket)
};

//Se anche lui
DigitalParamPacket digital_params[DIGITAL_MAX] = {
	{
		.header.header.type=DIGITAL_PARAM_PACKET_ID,
		.header.header.size=sizeof(DigitalParamPacket),
		.header.index=0
	},
	{
		.header.header.type=DIGITAL_PARAM_PACKET_ID,
		.header.header.size=sizeof(DigitalParamPacket),
		.header.index=1
	},
	{
		.header.header.type=DIGITAL_PARAM_PACKET_ID,
		.header.header.size=sizeof(DigitalParamPacket),
		.header.index=2
	},
	{
		.header.header.type=DIGITAL_PARAM_PACKET_ID,
		.header.header.size=sizeof(DigitalParamPacket),
		.header.index=3
	},
	{
		.header.header.type=DIGITAL_PARAM_PACKET_ID,
		.header.header.size=sizeof(DigitalParamPacket),
		.header.index=4
	},
	{
		.header.header.type=DIGITAL_PARAM_PACKET_ID,
		.header.header.size=sizeof(DigitalParamPacket),
		.header.index=5
	},
	{
		.header.header.type=DIGITAL_PARAM_PACKET_ID,
		.header.header.size=sizeof(DigitalParamPacket),
		.header.index=6
	},
	{
		.header.header.type=DIGITAL_PARAM_PACKET_ID,
		.header.header.size=sizeof(DigitalParamPacket),
		.header.index=7
	}
};

AnalogParamPacket analog_params[ANALOG_MAX] = {
	{
		.header.header.type=ANALOG_PARAM_PACKET_ID,
		.header.header.size=sizeof(AnalogParamPacket),
		.header.index=0
	},
	{
		.header.header.type=ANALOG_PARAM_PACKET_ID,
		.header.header.size=sizeof(AnalogParamPacket),
		.header.index=1
	},
	{
		.header.header.type=ANALOG_PARAM_PACKET_ID,
		.header.header.size=sizeof(AnalogParamPacket),
		.header.index=2
	},
	{
		.header.header.type=ANALOG_PARAM_PACKET_ID,
		.header.header.size=sizeof(AnalogParamPacket),
		.header.index=3
	},
	{
		.header.header.type=ANALOG_PARAM_PACKET_ID,
		.header.header.size=sizeof(AnalogParamPacket),
		.header.index=4
	},
	{
		.header.header.type=ANALOG_PARAM_PACKET_ID,
		.header.header.size=sizeof(AnalogParamPacket),
		.header.index=5
	},
	{
		.header.header.type=ANALOG_PARAM_PACKET_ID,
		.header.header.size=sizeof(AnalogParamPacket),
		.header.index=6
	},
	{
		.header.header.type=ANALOG_PARAM_PACKET_ID,
		.header.header.size=sizeof(AnalogParamPacket),
		.header.index=7
	}
};

void Smarthouse_shellStart(void)
{
	printf("shell started\n");
	while (run)
	{
		char *buffer = readline("Smarthouse>\t");
		if (buffer)
		{
			executeCommand(buffer);
			free(buffer);
		}
		else
		{ run=0;}
	}
}

