#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "smarthouse_shell.h"
#include "packet_header.h"

uint8_t idx;

int quitFn(void)
{
	run=0;
	return 0;
}

int ledOffFn(void)
{
/*
	digital_config.set_digital=ledOff;
	printf("Insert pin:\n");
	uint8_t pin;
	scanf("%d", &pin);	
	digital_config.pin_digital= pin;
	pointer_packet=(PacketHeader*)&digital_config;
*/
	idx=10;
	digital_config.pin_digital= idx;
	digital_config.set_digital=ledOff;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int ledOnFn(void)
{
/*
	digital_config.set_digital=ledOn;
	printf("Insert pin:\n");
	uint8_t pin;
	scanf("%d", &pin);	
	digital_config.pin_digital= pin;
	pointer_packet=(PacketHeader*)&digital_config;
*/
	idx=10;
	digital_config.pin_digital= idx;
	digital_config.set_digital=ledOn;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int dimmerFn(void)
{
/*
	digital_config.set_digital=dimmer;
	uint8_t intensity=0, pin;
	printf("insert pin:\n");
	scanf("%d", &pin);	
	digital_config.pin_digital= pin;
	pointer_packet=(PacketHeader*)&digital_config;
*/
	uint8_t pint = (uint8_t)pin;
	digital_config[index].pin_digital=index;
	digital_config.set_digital=dimmer;
	printf("Insert intensity:\n");
	if(control>=0)
	{
		digital_config.intensity=(uint8_t)intensity%256;
		pointer_packet=(PacketHeader*)&digital_config;
		return 0;
	}
	else
	{	return -1;	}
*/
return 0;
}

int digitalInputFn(void)
{
/*
	digital_config.set_digital=input_digital;
	uint8_t pin;
	printf("insert pin:\n");
	scanf("%d", &pin);
	digital_config.pin_digital=pin;
	pointer_packet=(PacketHeader*)&digital_config;
*/	return 0;
}

int adcFn(void)
{/*
	uint8_t sample, pin;
	printf ("Insert pin\n");
	scanf("%d", &pin);
	analog_config.pin_analog=pin;
	printf("Insert number of samples:\n");
	if(scanf("%d", &sample)>=0)
	{
		analog_config.samples=sample;
		pointer_packet=(PacketHeader*)&analog_config;
		return 0;
	}
	else
	{	return -1;	}
*/
return 0;
}

int requestFn(void)
{
/*
	uint8_t pin;
	printf("Insert pin:\n");
	scanf("%d", &pin);
	char *type;
	printf("insert type of status packet:\n");
	scanf("%s", &type);
	if(strcmp(type, "digital")==0)
	{
		pointer_packet=(PacketHeader*)digital_status[pin];	
	}
	else if(strcmp(type, "analog")==0)
	{
		pointer_packet=(PacketHeader*)analog_status[pin];
	}
	else
	{
		printf("Error, insert incorrect type of status packet\n");
	}
*/
	idx=10;
	digital_status[idx].pin_digital=idx;
	pointer_packet=(PacketHeader*)&digital_status[idx];
//	pointer_packet=(PacketHeader*)analog_status[idx];
	return 0;
}
Command commands[] =
{
	{
		.name = "quit",
		.cmd_fn=quitFn,
		.help="usage: quit"
	},
	{
		.name = "ledOff",
		.cmd_fn=ledOffFn,
		.help="usage: ledOff"
	},
	{
		.name = "ledOn",
		.cmd_fn=ledOnFn,
		.help="usage: ledOn"
	},
	{
		.name = "dimmer",
		.cmd_fn=dimmerFn,
		.help="usage: dimmer"
	},
	{
		.name = "digital_input",
		.cmd_fn=digitalInputFn,
		.help="usage: digital_input"
	},
	{
		.name = "adc",
		.cmd_fn=adcFn,
		.help="usage: adc"
	},
	{
		.name= "request",
		.cmd_fn=requestFn,
		.help="usage: request"
	}
};

const int num_commands=sizeof(commands)/sizeof(Command);

Command* findCommand(const char* name)
{
	int cmd_idx=0;
	while(cmd_idx<num_commands)
	{
		if (! strcmp(commands[cmd_idx].name, name))
		{
			return &commands[cmd_idx];
		}
		cmd_idx++;
	}
	return 0;
}

int executeCommand(const char* name)
{

/*	char line[1024];
	strcpy(line, line_);
  	char* name=strtok(line," ");
*/	if (! name)
		return -1;
	Command* cmd=findCommand(name);
  	if (! cmd)
	{
		printf("ERROR: unknown command [%s]\n", name);
		return -1;
	}
	int retval=0;
	if (cmd->cmd_fn)
	{
		retval=(*cmd->cmd_fn)();
		if (retval)
		{	printf("ERROR %d\n", retval);	}
		else
		{	printf("Packet transmitt\n");		}
	}
	else
	{	printf("ERROR: no handler for command\n");	}
	return retval;
}

