#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "smarthouse_shell.h"
#include "packet_header.h"
int setPin(void)
{
	int pin;
	printf("insert pin:\n");
	int control=scanf("%d\n", &pin);
	if(pin >=0 && pin<=15 && control>=0)
	{	return pin;	}
	else
	{	return -1;	}
}

int quitFn(void)
{
	run=0;
	return 0;
}

int ledOffFn(void)
{
	int set_pin=setPin();
	if(set_pin<=-1)
	{	return -1;	}
	digital_config.pin_digital=(uint8_t)set_pin;
	digital_config.set_digital=ledOff;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int ledOnFn(void)
{
	uint8_t set_pin=setPin();
	if(set_pin<=-1)
	{	return -1;	}
	digital_config.pin_digital=set_pin;
	digital_config.set_digital=ledOn;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int dimmerFn(void)
{
	int intensity=0;
	int set_pin=setPin();
	if(set_pin<=-1)
	{	return -1;	}
	digital_config.pin_digital=(uint8_t)set_pin;
	digital_config.set_digital=dimmer;
	printf("Insert intensity:\n");
	int control = scanf("%d", &intensity);
	if(control>=0)
	{
		digital_config.intensity=(uint8_t)intensity%256;
		pointer_packet=(PacketHeader*)&digital_config;
		return 0;
	}
	else
	{	return -1;	}
}

int digitalInputFn(void)
{
	int set_pin=setPin();
	if(set_pin<=-1)
	{	return -1;	}
	digital_config.pin_digital=(uint8_t)set_pin;
	digital_config.set_digital=input_digital;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int adcFn(void)
{
	int sample;
	int set_pin=setPin();
	if(set_pin<=-1)
	{	return -1;	}
	analog_config.pin_analog=(uint8_t)set_pin;
	printf("Insert number of samples:\n");
	if(scanf("%d", &sample)>=0)
	{
		analog_config.samples=(uint8_t)sample;
		pointer_packet=(PacketHeader*)&analog_config;
		return 0;
	}
	else
	{	return -1;	}
}

int requestFn(void)
{
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

int executeCommand(const char* line_)
{

	char line[1024];
	strcpy(line, line_);
  	char* name=strtok(line," ");
	if (! name)
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