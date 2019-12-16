#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "smarthouse_shell.h"
#include "packet_header.h"

uint8_t pin;

int quitFn(void)
{
	run=0;
	return 0;
}

int ledOffFn(void)
{
	digital_config.pin_digital=pin;
	digital_config.set_digital=ledOff;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int ledOnFn(void)
{
	
	digital_config.pin_digital= pin;
	digital_config.set_digital=ledOn;
	pointer_packet=(PacketHeader*)&digital_config;
	return 0;
}

int dimmerFn(void)
{	
	digital_config.pin_digital= pin;
	digital_config.set_digital=dimmer;
/*
	digital_config.intensity=(uint8_t)intensity%256;
	return 0;
*/
return 0;
}

int digitalInputFn(void)
{
	digital_config.pin_digital=pin;
	digital_config.set_digital=input_digital;
	return 0;
}

int adcFn(void)
{
	digital_config.pin_digital=pin;
	
/*
	int sample;
	int pin;
	printf ("Insert pin\n");

	uint8_t pint = (uint8_t)pin;
	printf("Insert number of samples:\n");
	if(scanf("%d", &sample)>=0)
	{
		analog_config.samples=(uint8_t)sample;
	return 0;
*/
return 0;
}

int requestFn(void)
{
	/*char insert[20];
	printf("Insert the status packet type\t(Es. digital\tor\tanalog)\n");
	scanf("%s", insert);
	if(strcmp(insert, "digital"))
	{
		digital_status.pin_digital=setPin();
		pointer_packet=(PacketHeader*)&digital_status;
	}
	else if(strcmp(insert,"analog"))
	{
		analog_status.pin_analog=setPin();
		pointer_packet=(PacketHeader*)&analog_status;
	}
	else
	{
		printf("Error status packet\n");
	}*/
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
	printf ("%s\n",line);
  	char* name=strtok(line," ");
//	name=strtok(NULL," ");
//		printf("[%s]\n", name);
//	if (! name)
//		return -1;
	Command* cmd=findCommand(name);
  	if (! cmd)
	{
		printf("ERROR: unknown command [%s]\n", name);
		return -1;
	}
//
	char *pint=strtok(NULL, " "); 
printf("pin inserito %s\n", pint);
/*	if(pint[1]!=NULL)
	{
		pin=atoi(pint[0])*10+atoi(pint[1]);
	}
	else { pin=atoi(pint[0]);}
	printf("Pin inserito=%d\n", pin);
*/
//	char *arg=strtok(NULL, " "); //intensity, samples, request type
//
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

